/* Exit Games Photon Voice - C++ Client Lib
 * Copyright (C) 2004-2021 by Exit Games GmbH. All rights reserved.
 * http://www.photonengine.com
 * mailto:developer@photonengine.com
 */

#include "PhotonVoice-cpp/inc/AudioOutDelayControl.h"

 /** @file PhotonVoice-cpp/inc/AudioOutDelayControl.h */

namespace ExitGames
{
	namespace Voice
	{
		using namespace Common;

		AudioOutDelayConfig::AudioOutDelayConfig(int low, int high, int max, int speedUpPerc) 
			: mLow(low)
			, mHigh(high)
			, mMax(max)
			, mSpeedUpPerc(speedUpPerc)
		{}

		int AudioOutDelayConfig::getLow() const {
			return mLow;
		}

		int AudioOutDelayConfig::getHigh() const {
			return mHigh;
		}
		int AudioOutDelayConfig::getMax() const {
			return mMax;
		}

		int AudioOutDelayConfig::getSpeedUpPerc() const {
			return mSpeedUpPerc;
		}

		template<typename T>
		AudioOutDelayControl<T>::AudioOutDelayControl(const ILogger& logger, AudioOutDelayConfig delayConfig, const Common::JString& logPrefix, bool debugInfo)
			: mLogger(logger)
			, mLogPrefix(logPrefix)
			, mFrameSamples(0)
			, mFrameSize(0)
			, mWriteSamplePos(0)
			, mPlaySamplePos(0)
			, mOutPosPrev(0)
			, mPlayLoopCount(0)
			, mDelayConfig(delayConfig)
			, mStarted(false)
			, mFlushed(true)
			, mTargetDelaySamples(0)
			, mUpperTargetDelaySamples(0)
			, mMaxDelaySamples(0)
			, mLastPushTime(GETTIMEMS() - NO_PUSH_TIMEOUT_MS)
			, mDebugInfo(debugInfo)
			, mTempoChangeHQ(false)
			, mCatchingUp(false)
		{
		}

		template<typename T>
		int AudioOutDelayControl<T>::getLag(void) const
		{
			return (int)((mWriteSamplePos - (mStarted ? mPlaySamplePos.load() : 0.0f)) * 1000 / mFrequency);
		}

		template<typename T>
		bool AudioOutDelayControl<T>::isFlushed() const
		{
			return !mStarted || mFlushed;
		}

		template<typename T>
		bool AudioOutDelayControl<T>::isPlaying() const
		{
			return !isFlushed() && (GETTIMEMS() - mLastPushTime < NO_PUSH_TIMEOUT_MS);
		}

		template<typename T>
		void AudioOutDelayControl<T>::start(int frequency, int channels, int frameSamples)
		{
			//frequency = (int)(frequency * 1.2); // underrun test
			//frequency = (int)(frequency / 1.2); // overrun test
			mFrequency = frequency;
			mChannels = channels;
			// add 1 frame samples to make sure that we have something to play when delay set to 0
			mTargetDelaySamples = mDelayConfig.getLow() * frequency / 1000 + frameSamples;
			mUpperTargetDelaySamples = mDelayConfig.getHigh() * frequency / 1000 + frameSamples;
			if (mUpperTargetDelaySamples < mTargetDelaySamples + 2 * frameSamples)
			{
				mUpperTargetDelaySamples = mTargetDelaySamples + 2 * frameSamples;
			}

			mMaxDelaySamples = mDelayConfig.getMax() * frequency / 1000;
			if (mMaxDelaySamples < mUpperTargetDelaySamples)
			{
				mMaxDelaySamples = mUpperTargetDelaySamples;
			}

			mBufferSamples = 3 * mMaxDelaySamples; // make sure we have enough space
			mFrameSamples = frameSamples;
			mFrameSize = frameSamples * channels;

			mWriteSamplePos = mTargetDelaySamples;

			mZeroFrame = Buffer<T>(mFrameSize);
			memset(mZeroFrame.getArray(), 0, mZeroFrame.getSize() * sizeof(T));
			mResampledFrame = Buffer<T>(mFrameSize);

			mTempoChangeHQ = false;

			outCreate(frequency, channels, mBufferSamples);
			outStart();
			mStarted = true;
			mLogger.logInfo(mLogPrefix + L" Start: " + (sizeof(T) == 2 ? L"short" : L"float") + L" bs=" + mBufferSamples + L" ch=" + channels + L" f=" + frequency + L" tds=" + mTargetDelaySamples + L" utds=" + mUpperTargetDelaySamples + L" mds=" + mMaxDelaySamples + L" speed=" + mDelayConfig.getSpeedUpPerc() + L" tempo=" + (mTempoChangeHQ ? L"HQ" : L"LQ"));
		}

		template<typename T>
		void AudioOutDelayControl<T>::logDebug(Common::JString const & header, int lagSamples, int64 playSamplePos) const
		{
			if (mDebugInfo)
			{
				mLogger.logDebug(mLogPrefix + L" "  + header + L" "  + mUpperTargetDelaySamples + L" " + lagSamples + L" " + playSamplePos + L" " + mWriteSamplePos + L" " + (playSamplePos + mTargetDelaySamples));
			}
		}

		template<typename T>
		bool AudioOutDelayControl<T>::processFrame(Buffer<T> frame, int64 playSamplePos, bool flush)
		{
			int lagSamples = static_cast<int>(mWriteSamplePos - playSamplePos);
			if (!mFlushed)
			{
				if (lagSamples > mMaxDelaySamples)
				{
					logDebug(L"overrun", lagSamples, playSamplePos);
					mWriteSamplePos = playSamplePos + mMaxDelaySamples;
					lagSamples = mMaxDelaySamples;
				}
				else if (lagSamples < 0)
				{
					logDebug(L"underrun", lagSamples, playSamplePos);
					mWriteSamplePos = playSamplePos + mTargetDelaySamples;
					lagSamples = mTargetDelaySamples;
				}
			}

			if (flush) // flush signalled
			{
				mFlushed = true;
				logDebug(L"stream flush pause", lagSamples, playSamplePos);
				if (mCatchingUp)
				{
					mCatchingUp = false;
					logDebug(L"stream sync reset", lagSamples, playSamplePos);
				}
				return true;
			}
			else
			{
				if (mFlushed)
				{
					mWriteSamplePos = playSamplePos + mTargetDelaySamples;
					lagSamples = mTargetDelaySamples;
					mFlushed = false;
					logDebug(L"stream unpause", lagSamples, playSamplePos);
				}
			}

			// starting catching up
			if (lagSamples > mUpperTargetDelaySamples && !mCatchingUp)
			{
				if (!mTempoChangeHQ)
				{
					mTempoUp.begin(mChannels, mDelayConfig.getSpeedUpPerc(), TEMPO_UP_SKIP_GROUP);
				}
				mCatchingUp = true;
				logDebug(L"stream sync started", lagSamples, playSamplePos);
			}

			// finishing catching up
			bool frameIsWritten = false; // first frame after switching from catching up requires special processing to flush TempoUp (the end of skipping wave removed if required)
			if (lagSamples <= mTargetDelaySamples && mCatchingUp)
			{
				if (!mTempoChangeHQ)
				{
					int skipSamples = mTempoUp.end(frame);
					int resampledLenSamples = frame.getSize() / mChannels - skipSamples;
					memcpy(mResampledFrame.getArray(), frame.getArray() + skipSamples * mChannels, resampledLenSamples * mChannels * sizeof(T));
					writeResampled(mResampledFrame, resampledLenSamples);
					frameIsWritten = true;
				}
				mCatchingUp = false;
				logDebug(L"stream sync finished", lagSamples, playSamplePos);
			}

			if (frameIsWritten)
			{
				return false;
			}

			if (mCatchingUp)
			{
				if (!mTempoChangeHQ)
				{
					int resampledLenSamples = mTempoUp.process(frame, mResampledFrame);
					writeResampled(mResampledFrame, resampledLenSamples);
				}
			}
			else
			{
				outWrite(frame, mWriteSamplePos % mBufferSamples);
				mWriteSamplePos += frame.getSize() / mChannels;
			}

			return false;
		}

		template<typename T>
		void AudioOutDelayControl<T>::service()
		{
			if (mStarted)
			{
				// cache PlayerPos
				int64 outPos = outGetPos();
				// loop detection (pcmsetpositioncallback not called when clip loops)
				if (outPos < mOutPosPrev)
				{
					mPlayLoopCount++;
				}
				mOutPosPrev = outPos;

				int64 clearStart = mPlaySamplePos;

				mPlaySamplePos = mPlayLoopCount * mBufferSamples + outPos;

				int64 clearMin = mPlaySamplePos - mBufferSamples;
				
				if (clearStart < clearMin)
				{
					clearStart = clearMin;
				}
				// zero the part of the buffer already played
				int64 framesToClear = (mPlaySamplePos - clearStart - 1) / mFrameSamples + 1;
				for (int64 offset = mPlaySamplePos - framesToClear * mFrameSamples; offset < mPlaySamplePos; offset += mFrameSamples)
				{
					int o = offset % mBufferSamples;
					if (o < 0) o += mBufferSamples;
					outWrite(mZeroFrame, o);
				}
			}
		}

		template<typename T>
		int AudioOutDelayControl<T>::writeResampled(Buffer<T> f, int resampledLenSamples)
		{
			// zero not used part of the buffer because SetData applies entire frame
			// if this frame is the last, grabage may be played back
			int tailSize = (f.getSize() - resampledLenSamples * mChannels) * sizeof(T);
			if (tailSize > 0) // it may be 0 what BlockCopy does not like
			{
				memset(f.getArray() + resampledLenSamples * mChannels, 0, tailSize);
			}

			outWrite(f, mWriteSamplePos % mBufferSamples);
			mWriteSamplePos += resampledLenSamples;
			return resampledLenSamples;
		}

		template<typename T>
		void AudioOutDelayControl<T>::push(Buffer<T> frame)
		{
			if (!mStarted)
				return;

			if (frame.getSize() == 0)
				return;

			if (frame.getSize() != mFrameSize)
			{
				mLogger.logError(mLogPrefix + L" audio frames are not of size: " + frame.getSize() + " != " + mFrameSize);
				return;
			}

			processFrame(frame, mPlaySamplePos, false);
			mLastPushTime = GETTIMEMS();
		}

		template<typename T>
		void AudioOutDelayControl<T>::flush()
		{
			processFrame(Buffer<T>::getEmpty(), mPlaySamplePos, true);
		}

		template<typename T>
		void AudioOutDelayControl<T>::stop(void)
		{
			mStarted = false;
		}

		template class AudioOutDelayControl<float>;
		template class AudioOutDelayControl<short>;
	}
}