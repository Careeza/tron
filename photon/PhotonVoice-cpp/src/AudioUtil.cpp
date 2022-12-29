/* Exit Games Photon Voice - C++ Client Lib
 * Copyright (C) 2004-2022 Exit Games GmbH. All rights reserved.
 * http://www.photonengine.com
 * mailto:developer@photonengine.com
 */

#include "PhotonVoice-cpp/inc/AudioUtil.h"

/** @file PhotonVoice-cpp/inc/AudioUtil.h */

namespace ExitGames
{
	namespace Voice
	{
		/// <summary>Collection of Audio Utility functions and classes.</summary>
		namespace AudioUtil
		{
			using namespace Common;
			using namespace Common::MemoryManagement;

			/// <summary>Resample audio data so that the complete src buffer fits into dstSamples in the dst buffer. The buffers contain audio with the same number of channels.</summary>
			/// This implements a primitive nearest-neighbor resampling algorithm for an arbitrary number of channels.
			/// <param name="srcBuf">Source buffer.</param>
			/// <param name="dstBuf">Destination buffer.</param>
			/// <param name="dstSamples">Destination data size in samples.</param>
			/// <param name="channels">Number of audio channels.</param>
			template<typename T>
			void resample(const Buffer<T>& srcBuf, Buffer<T>& dstBuf, int dstSamples, int channels)
			{
				resample(srcBuf, 0, srcBuf.getSize() / channels, dstBuf, 0, dstSamples, channels);
			}

			/// <summary>Resample audio data with offsets and sizes specified for both src and dst buffers. The buffers contain audio with the same number of channels.</summary>
			/// This implements a primitive nearest-neighbor resampling algorithm for an arbitrary number of channels.
			/// <param name="srcBuf">Source buffer.</param>
			/// <param name="srcOffsetSamples">Source data offset in samples.</param>
			/// <param name="srcSamples">Source data size in samples.</param>
			/// <param name="dstBuf">Destination buffer.</param>
			/// <param name="dstOffsetSamples">Destination data offset in samples.</param>
			/// <param name="dstSamples">Destination data size in samples.</param>
			/// <param name="channels">Number of audio channels.</param>
			template<typename T>
			void resample(const Buffer<T>& srcBuf, int srcOffsetSamples, int srcSamples, Buffer<T>& dstBuf, int dstOffsetSamples, int dstSamples, int channels)
			{
				const T* src = srcBuf.getArray() + srcOffsetSamples * channels;
				T* dst = dstBuf.getArray() + dstOffsetSamples * channels;

				if(dstSamples == srcSamples)
				{
					int i = dstSamples * channels;
					while(i--)
						*dst++ = *src++;

					return;
				}

				if(channels == 1)
					for(int i=0; i<dstSamples; i++)
						*dst++ = src[i * srcSamples / dstSamples];
				else if(channels == 2)
				{
					for(int i=0; i<dstSamples; i++)
					{
						const T* s = src + i * srcSamples / dstSamples * 2;
						*dst++ = *s++;
						*dst++ = *s;
					}
				}
				else
				{
					for(int i=0; i<dstSamples; i++)
					{
						const T* s = src + i * srcSamples / dstSamples * channels;
						int j = channels;
						while(j--)
							*dst++ = *s++;
					}
				}
			}


			/// <summary>Resample audio data with offsets and sizes specified for both src and dst buffers.</summary>
			/// This implements a primitive nearest-neighbor resampling algorithm for an arbitrary number of channels.
			/// <param name="srcBuf">Source buffer.</param>
			/// <param name="srcOffsetSamples">Source data offset in samples.</param>
			/// <param name="srcSamples">Source data size in samples.</param>
			/// <param name="srcChannels">Number of audio channels in source.</param>
			/// <param name="dstBuf">Destination buffer.</param>
			/// <param name="dstOffsetSamples">Destination data offset in samples.</param>
			/// <param name="dstSamples">Destination data size in samples.</param>
			/// <param name="dstChannels">Number of audio channels in destination.</param>
			template<typename T>
			void resample(const Buffer<T>& srcBuf, int srcOffsetSamples, int srcSamples, int srcChannels, Buffer<T>& dstBuf, int dstOffsetSamples, int dstSamples, int dstChannels)
			{
				if(srcChannels == dstChannels)
				{
					resample<T>(srcBuf, srcOffsetSamples, srcSamples, dstBuf, dstOffsetSamples, dstSamples, dstChannels);
					return;
				}

				const T* src = srcBuf.getArray() + srcOffsetSamples * srcChannels;
				T* dst = dstBuf.getArray() + dstOffsetSamples * dstChannels;

				if(dstSamples == srcSamples)
				{
					if(dstChannels == 2 && srcChannels == 1)
					{
						int i = dstSamples;
						while(i--)
						{
							*dst++ = *src;
							*dst++ = *src++;
						}
					}
					else if(dstChannels == 1 && srcChannels == 2)
					{
						int i = dstSamples;
						while (i--)
						{
							*dst++ = (src[0] + src[1]) / 2;
							src += 2;
						}
					}
					else
					{
						// mix src to mono and copy the result to all dst channels
						int i = dstSamples;
						while(i--)
						{
							T v = *src++;
							int sc = srcChannels-1;
							while(sc--)
								v += *src++;

							v /= srcChannels;

							int dc = dstChannels;
							while(dc--)
								*dst++ = v;
						}
					}

					return;
				}

				if(srcChannels == 1 && dstChannels == 2)
				{
					for(int i=0; i<dstSamples; i++)
					{
						T v = src[i * srcSamples / dstSamples];
						*dst++ = v;
						*dst++ = v;
					}
				}
				else if(srcChannels == 2 && dstChannels == 1)
				{
					for(int i=0; i<dstSamples; i++)
					{
						int j = i * srcSamples / dstSamples * 2;
						*dst++ = (src[j] + src[j + 1]) / 2;
					}
				}
				else
				{
					// mix src to mono and copy the result to all dst channels
					for(int i=0; i<dstSamples; i++)
					{
						const T* s = src + i * srcSamples / dstSamples * srcChannels;
						T v = *s++;
						int sc = srcChannels - 1;
						while(sc--)
							v += *s++;

						v /= srcChannels;

						int dc = dstChannels;
						while(dc--)
							*dst++ = v;
					}
				}
			}

			/// <summary>Resample audio data so that the complete src buffer fits into dstCount samples in the dst buffer,
			/// and convert short to float samples along the way.</summary>
			/// This implements a primitive nearest-neighbor resampling algorithm for an arbitrary number of channels.
			/// <param name="srcBuf">Source buffer.</param>
			/// <param name="dstBuf">Destination buffer.</param>
			/// <param name="dstCount">Target size of destination buffer (in samples per channel).</param>
			/// <param name="channels">Number of channels in the signal (1=mono, 2=stereo). Must be > 0.</param>
			void resampleAndConvert(const Buffer<short>& srcBuf, Buffer<float>& dstBuf, int dstCount, int channels)
			{
				const short* src = srcBuf.getArray();
				float* dst = dstBuf.getArray();
				int srcCount = srcBuf.getSize();
				if(channels == 1)
					for(int i=0; i<dstCount; i++)
						dst[i] = src[i*srcCount/dstCount]/static_cast<float>(SHRT_MAX);
				else if(channels == 2)
				{
					for(int i=0; i<dstCount/2; i++)
					{
						int srcI = i*srcCount/dstCount;
						int dstCh0I = i*2;
						int srcCh0I = srcI*2;
						dst[dstCh0I++] = src[srcCh0I++]/static_cast<float>(SHRT_MAX);
						dst[dstCh0I] = src[srcCh0I]/static_cast<float>(SHRT_MAX);
					}
				}
				else
				{
					for(int i=0; i<dstCount/channels; i++)
					{
						int srcI = i*srcCount/dstCount;
						int dstCh0I = i*channels;
						int srcCh0I = srcI*channels;
						for(int ch=0; ch<channels; ch++)
							dst[dstCh0I++] = src[srcCh0I++]/static_cast<float>(SHRT_MAX);
					}
				}
			}

			/// <summary>Resample audio data so that the complete src buffer fits into dstCount samples in the dst buffer,
			/// and convert float to short samples along the way.</summary>
			/// This implements a primitive nearest-neighbor resampling algorithm for an arbitrary number of channels.
			/// <param name="srcBuf">Source buffer.</param>
			/// <param name="dstBuf">Destination buffer.</param>
			/// <param name="dstCount">Target size of destination buffer (in samples per channel).</param>
			/// <param name="channels">Number of channels in the signal (1=mono, 2=stereo). Must be > 0.</param>
			void resampleAndConvert(const Buffer<float>& srcBuf, Buffer<short>& dstBuf, int dstCount, int channels)
			{
				const float* src = srcBuf.getArray();
				short* dst = dstBuf.getArray();
				int srcCount = srcBuf.getSize();
				if(channels == 1)
					for(int i=0; i<dstCount; i++)
						dst[i] = static_cast<short>(src[i*srcCount/dstCount]*static_cast<float>(SHRT_MAX));
				else if(channels == 2)
				{
					for(int i=0; i<dstCount/2; i++)
					{
						int srcI = i*srcCount/dstCount;
						int dstCh0I = i*2;
						int srcCh0I = srcI*2;
						dst[dstCh0I++] = static_cast<short>(src[srcCh0I++]*static_cast<float>(SHRT_MAX));
						dst[dstCh0I] = static_cast<short>(src[srcCh0I]*static_cast<float>(SHRT_MAX));
					}
				}
				else
				{
					for(int i=0; i<dstCount/channels; i++)
					{
						int srcI = i*srcCount/dstCount;
						int dstCh0I = i*channels;
						int srcCh0I = srcI*channels;
						for(int ch=0; ch<channels; ch++)
							dst[dstCh0I++] = static_cast<short>(src[srcCh0I++]*static_cast<float>(SHRT_MAX));
					}
				}
			}

			/// <summary>Convert audio buffer from float to short samples.</summary>
			/// <param name="srcBuf">Source buffer.</param>
			/// <param name="dstBuf">Destination buffer.</param>
			/// <param name="dstCount">Size of destination buffer (in total samples), source buffer must be of same length or longer.</param>
			void convert(const Buffer<float>& srcBuf, Buffer<short>& dstBuf, int dstCount)
			{
				const float* src = srcBuf.getArray();
				short* dst = dstBuf.getArray();
				for(int i=0; i<dstCount; i++)
					dst[i] = static_cast<short>(src[i]*static_cast<float>(SHRT_MAX));
			}

			/// <summary>Convert audio buffer from short to float samples.</summary>
			/// <param name="srcBuf">Source buffer.</param>
			/// <param name="dstBuf">Destination buffer.</param>
			/// <param name="dstCount">Size of destination buffer (in total samples), source buffer must be of same length or longer.</param>
			void convert(const Buffer<short>& srcBuf, Buffer<float>& dstBuf, int dstCount)
			{
				const short* src = srcBuf.getArray();
				float* dst = dstBuf.getArray();
				for(int i=0; i<dstCount; i++)
					dst[i] = src[i]/static_cast<float>(SHRT_MAX);
			}


			/// <summary>Convert audio buffer with arbitrary number of channels to stereo.</summary>
			/// For mono sources (srcChannels==1), the signal will be copied to both Left and Right stereo channels.
			/// For all others, the first two available channels will be used, any other channels will be discarded.
			/// <param name="srcBuf">Source buffer.</param>
			/// <param name="dstBuf">Destination buffer.</param>
			/// <param name="srcChannels">Number of (interleaved) channels in src.</param>
			template<typename T>
			void forceToStereo(const Buffer<T>& srcBuf, Buffer<T>& dstBuf, int srcChannels)
			{
				T* src = srcBuf.getArray();
				T* dst = dstBuf.getArray();
				for(int i=0, j=0; j<dst->Length-1; i+=srcChannels, j+=2)
				{
					dst[j] = src[i];
					dst[j + 1] = srcChannels > 1 ? src[i + 1] : src[i];
				}
			}

			template<typename T>
			Resampler<T>::Resampler(int dstSamples, int channels)
				: dstBuf(dstSamples * channels)
				, mChannels(channels)
			{
			}

			template<typename T>
			Buffer<T> Resampler<T>::process(Buffer<T> buf)
			{
				resample(buf, dstBuf, dstBuf.getSize() / mChannels, mChannels);
				return dstBuf;
			}

			/// <summary>Create new LevelMeterFloat instance.</summary>
			/// <param name="samplingRate">Sampling rate of the audio signal (in Hz).</param>
			/// <param name="numChannels">Number of channels in the audio signal.</param>
			template<typename T>
			LevelMeter<T>::LevelMeter(int samplingRate, int numChannels)
				: mAmpSum(0)
				, mAmpPeak(0)
				, mPrevValues(samplingRate*numChannels/2) // 1/2 sec
				, mPrevValuesHead(0)
				, mAccumAvgPeakAmpSum(0)
				, mAccumAvgPeakAmpCount(0)
				, mCurrentPeakAmp(0)
			{
			}

			template<typename T>
			float LevelMeter<T>::getCurrentAvgAmp(void) const
			{
				return mAmpSum/mPrevValues.getSize();
			}

			template<typename T>
			float LevelMeter<T>::getCurrentPeakAmp(void) const
			{
				return mCurrentPeakAmp;
			}

			template<typename T>
			float LevelMeter<T>::getAccumAvgPeakAmp(void) const
			{
				return !mAccumAvgPeakAmpCount ? 0 : mAccumAvgPeakAmpSum/mAccumAvgPeakAmpCount;
			}

			template<typename T>
			void LevelMeter<T>::resetAccumAvgPeakAmp(void)
			{
				mAccumAvgPeakAmpSum = 0;
				mAccumAvgPeakAmpCount = 0;
				mAmpPeak = 0;
			}

			template<typename T>
			Buffer<T> LevelMeter<T>::process(Buffer<T> buf)
			{
				T* v = buf.getArray();
				for(int i=0; i<buf.getSize(); i++, v++)
				{
					T a = *v;
					if(a < 0)
						a = -a;
					mAmpSum = mAmpSum + a - mPrevValues.getArray()[mPrevValuesHead];
					mPrevValues.getArray()[mPrevValuesHead] = a;

					if(mAmpPeak < a)
						mAmpPeak = a;
					if(!mPrevValuesHead)
					{
						mCurrentPeakAmp = mAmpPeak;
						mAmpPeak = 0;
						mAccumAvgPeakAmpSum += mCurrentPeakAmp;
						mAccumAvgPeakAmpCount++;
					}
					mPrevValuesHead = (mPrevValuesHead + 1) % buf.getSize();
				}
				return buf;
			}

			template<typename T>
			bool VoiceDetectorCalibration<T>::isCalibrating(void) const
			{
				return mCalibrateCount > 0;
			}

			/// <summary>Create new VoiceDetectorCalibration instance.</summary>
			/// <param name="pVoiceDetector">Voice Detector to calibrate.</param>
			/// <param name="pLevelMeter">Level Meter to look at for calibration.</param>
			/// <param name="samplingRate">Sampling rate of the audio signal (in Hz).</param>
			/// <param name="channels">Number of channels in the audio signal.</param>
			template<typename T>
			VoiceDetectorCalibration<T>::VoiceDetectorCalibration(IVoiceDetector* pVoiceDetector, ILevelMeter* pLevelMeter, int samplingRate, int channels)
				: mpVoiceDetector(pVoiceDetector)
				, mpLevelMeter(pLevelMeter)
				, mValuesPerSec(samplingRate*channels)
				, mCalibrateCount(0)
			{
			}

			/// <summary>Start calibration.</summary>
			/// <param name="durationMs">Duration of the calibration procedure (in milliseconds).</param>
			/// This activates the Calibration process. 
			/// It will reset the given LevelMeter's AccumAvgPeakAmp (accumulated average peak amplitude),
			/// and when the duration has passed, use it for the VoiceDetector's detection threshold.
			template<typename T>
			void VoiceDetectorCalibration<T>::calibrate(int durationMs)
			{
				mCalibrateCount = mValuesPerSec*durationMs/1000;
				mpLevelMeter->resetAccumAvgPeakAmp();
			}

			template<typename T>
			Buffer<T> VoiceDetectorCalibration<T>::process(Buffer<T> buf)
			{
				if(mCalibrateCount)
				{
					mCalibrateCount -= buf.getSize();
					if(mCalibrateCount <= 0)
					{
						mCalibrateCount = 0;
						mpVoiceDetector->setThreshold(mpLevelMeter->getAccumAvgPeakAmp()*2);
					}
				}
				return buf;
			}

			template<typename T>
			Buffer<T> VoiceDetector<T>::process(Buffer<T> buffer)
			{
				if(mOn)
				{
					T* s = buffer.getArray();
					for(int i=0; i<buffer.getSize(); i++, s++)
					{
						if(*s > mThreshold)
						{
							setDetected(true);
							mAutoSilenceCounter = 0;
						}
						else
							mAutoSilenceCounter++;
					}
					if(mAutoSilenceCounter > mActivityDelayValuesCount)
						mDetected = false;

					return mDetected ? buffer : Buffer<T>::getEmpty();
				}
				else
					return buffer;
			}

			/// <summary>If true, voice detection enabled.</summary>
			template<typename T>
			bool VoiceDetector<T>::getOn(void) const
			{
				return mOn;
			}

			template<typename T>
			void VoiceDetector<T>::setOn(bool on)
			{
				mOn = on;
			}

			/// <summary>Voice detected as soon as signal level exceeds threshold.</summary>
			template<typename T>
			float VoiceDetector<T>::getThreshold(void) const
			{
				return mThreshold;
			}

			template<typename T>
			void VoiceDetector<T>::setThreshold(float value)
			{
				mThreshold = value;
			}

			template<typename T>
			bool VoiceDetector<T>::getDetected(void) const
			{
				return mDetected;
			}

			template<typename T>
			void VoiceDetector<T>::setDetected(bool value)
			{
				if(mDetected != value)
				{
					mDetected = value;
					mDetectedTime = GETTIMEMS();
					if(mDetected && mpOnDetected)
						mpOnDetected();
				}
			}
			/// <summary>Last time when switched to detected state.</summary>

			template<typename T>
			int VoiceDetector<T>::getDetectedTime(void) const
			{
				return mDetectedTime;
			}

			/// <summary>Called when switched to detected state.</summary>
			template<typename T>
			void VoiceDetector<T>::setOnDetected(void(*pCallback)(void))
			{
				mpOnDetected = pCallback;
			}

			/// <summary>Keep detected state during this time after signal level dropped below threshold.</summary>
			template<typename T>
			int VoiceDetector<T>::getActivityDelayMs(void) const
			{
				return mActivityDelayMs;
			}

			template<typename T>
			void VoiceDetector<T>::setActivityDelayMs(int value)
			{
				mActivityDelayMs = value;
				mActivityDelayValuesCount = value*mValuesCountPerSec/1000;
			}

			template<typename T>
			float defaultThreshold(void)
			{
				return 0;
			}

			template<>
			float defaultThreshold<float>(void)
			{
				return 0.01f;
			}

			template<>
			float defaultThreshold<short>(void)
			{
				return 0.01f*SHRT_MAX;
			}

			template<typename T>
			VoiceDetector<T>::VoiceDetector(int samplingRate, int numChannels)
				: mAutoSilenceCounter(0)
				, mValuesCountPerSec(samplingRate*numChannels)
				, mActivityDelayValuesCount(0)
				, mActivityDelayMs(0)
				, mOn(true)
				, mThreshold(defaultThreshold<T>())
				, mDetected(false)
				, mDetectedTime(0)
				, mpOnDetected(NULL)
			{
				setActivityDelayMs(500);
			}

			/// <summary>The LevelMeter in use.</summary>
			template<typename T>
			ILevelMeter* VoiceLevelDetectCalibrate<T>::getLevelMeter(void) const
			{
				return mpLevelMeter;
			}

			/// <summary>The VoiceDetector in use</summary>
			template<typename T>
			IVoiceDetector* VoiceLevelDetectCalibrate<T>::getDetector(void) const
			{
				return mpVoiceDetector;
			}

			/// <summary>Create new VoiceLevelDetectCalibrate instance</summary>
			/// <param name="samplingRate">Sampling rate of the audio signal (in Hz).</param>
			/// <param name="channels">Number of channels in the audio signal.</param>
			template<typename T>
			VoiceLevelDetectCalibrate<T>::VoiceLevelDetectCalibrate(int samplingRate, int channels)
				: mpLevelMeter(allocate<LevelMeter<T> >(samplingRate, channels))
				, mpVoiceDetector(allocate<VoiceDetector<T> >(samplingRate, channels))
				, mpCalibration(allocate<VoiceDetectorCalibration<T> >(mpVoiceDetector, mpLevelMeter, samplingRate, channels))
			{
			}

			template<typename T>
			VoiceLevelDetectCalibrate<T>::~VoiceLevelDetectCalibrate(void)
			{
				deallocate(mpLevelMeter);
				deallocate(mpVoiceDetector);
				deallocate(mpCalibration);
			}

			/// <summary>Start calibration</summary>
			/// <param name="durationMs">Duration of the calibration procedure (in milliseconds).</param>
			/// This activates the Calibration process. 
			/// It will reset the given LevelMeter's AccumAvgPeakAmp (accumulated average peak amplitude),
			/// and when the duration has passed, use it for the VoiceDetector's detection threshold.
			template<typename T>
			void VoiceLevelDetectCalibrate<T>::calibrate(int durationMs)
			{
				mpCalibration->calibrate(durationMs);
			}

			template<typename T>
			Buffer<T> VoiceLevelDetectCalibrate<T>::process(Buffer<T> buf)
			{
				return mpVoiceDetector->process(mpCalibration->process(mpLevelMeter->process(buf)));
			}

			template<typename T>
			TempoUp<T>::TempoUp()
				: mChannels(0)
				, mSkipGroup(0)
				, mSkipFactor(0)
				, mSign(0)
				, mWaveCnt(0)
				, mSkipping(0)
			{}

			template<typename T>
			void TempoUp<T>::begin(int channels, int changePerc, int skipGroup)
			{
				mChannels = channels;
				mSkipFactor = 100 / changePerc;
				mSkipGroup = skipGroup;
				mSign = 0;
				mSkipping = false;
				mWaveCnt = 0;
			}

			template<typename T>
			int TempoUp<T>::process(Buffer<T> sb, Buffer<T> db)
			{
				T* s = sb.getArray();
				T* d = db.getArray();
				int dPos = 0;
				if (mChannels == 1)
				{
					for (int i = 0; i < sb.getSize(); i++)
					{
						if (s[i] < 0)
						{
							mSign = -1;
						}
						else if (mSign < 0)
						{
							mWaveCnt++;
							mSkipping = mWaveCnt % (mSkipGroup * mSkipFactor) < mSkipGroup;
							mSign = 0;
						}

						if (!mSkipping)
						{
							d[dPos++] = s[i];
						}
					}
				}

				else if (mChannels == 2)
				{
					for (int i = 0; i < sb.getSize(); i += 2)
					{
						if (s[i] + s[i + 1] < 0)
						{
							mSign = -1;
						}
						else if (mSign < 0)
						{
							mWaveCnt++;
							mSkipping = mWaveCnt % (mSkipGroup * mSkipFactor) < mSkipGroup;
							mSign = 0;
						}

						if (!mSkipping)
						{
							d[dPos++] = s[i];
							d[dPos++] = s[i + 1];
						}
					}
				}

				else
				{
					for (int i = 0; i < sb.getSize(); i += mChannels)
					{
						T x = s[i] + s[i + 1];
						for (int j = 2; i < mChannels; j++)
						{
							x += s[i + j];
						}
						if (x < 0)
						{
							mSign = -1;
						}
						else if (mSign < 0)
						{
							mWaveCnt++;
							mSkipping = mWaveCnt % (mSkipGroup * mSkipFactor) < mSkipGroup;
							mSign = 0;
						}

						if (!mSkipping)
						{
							d[dPos++] = s[i];
							d[dPos++] = s[i + 1];
							for (int j = 2; i < mChannels; j++)
							{
								d[dPos++] += s[i + j];
							}
						}
					}
				}

				return dPos / mChannels;
			}

			template<typename T>
			int TempoUp<T>::end(Buffer<T> sb)
			{
				T* s = sb.getArray();
				if (mChannels == 1)
				{
					for (int i = 0; i < sb.getSize(); i++)
					{
						if (s[i] < 0)
						{
							mSign = -1;
						}
						else if (mSign < 0)
						{
							mWaveCnt++;
							mSkipping = mWaveCnt % (mSkipGroup * mSkipFactor) < mSkipGroup;
							if (!mSkipping)
							{
								return i;
							}
							mSign = 0;
						}
					}
				}

				else if (mChannels == 2)
				{
					for (int i = 0; i < sb.getSize(); i += 2)
					{
						if (s[i] + s[i + 1] < 0)
						{
							mSign = -1;
						}
						else if (mSign < 0)
						{
							mWaveCnt++;
							mSkipping = mWaveCnt % (mSkipGroup * mSkipFactor) < mSkipGroup;
							if (!mSkipping)
							{
								return i / 2;
							}
							mSign = 0;
						}
					}
				}

				else
				{
					for (int i = 0; i < sb.getSize(); i += mChannels)
					{
						T x = s[i] + s[i + 1];
						for (int j = 2; i < mChannels; j++)
						{
							x += s[i + j];
						}
						if (x < 0)
						{
							mSign = -1;
						}
						else if (mSign < 0)
						{
							mWaveCnt++;
							mSkipping = mWaveCnt % (mSkipGroup * mSkipFactor) < mSkipGroup;
							if (!mSkipping)
							{
								return i / mChannels;
							}
							mSign = 0;
						}
					}
				}
				return 0;
			}


			template class Resampler<float>;
			template class Resampler<short>;
			template class VoiceDetectorCalibration<float>;
			template class VoiceDetectorCalibration<short>;
			template class VoiceLevelDetectCalibrate<float>;
			template class VoiceLevelDetectCalibrate<short>;
			template class LevelMeter<float>;
			template class LevelMeter<short>;
			template class VoiceDetector<float>;
			template class VoiceDetector<short>;
			template class TempoUp<float>;
			template class TempoUp<short>;

			template void resample(const Buffer<float>& srcBuf, Buffer<float>& dstBuf, int dstSamples, int channels);
			template void resample(const Buffer<float>& srcBuf, int srcOffsetSamples, int srcSamples, Buffer<float>& dstBuf, int dstOffsetSamples, int dstSamples, int channels);
			template void resample(const Buffer<float>& srcBuf, int srcOffsetSamples, int srcSamples, int srcChannels, Buffer<float>& dstBuf, int dstOffsetSamples, int dstSamples, int dstChannels);

			template void resample(const Buffer<short>& srcBuf, Buffer<short>& dstBuf, int dstSamples, int channels);
			template void resample(const Buffer<short>& srcBuf, int srcOffsetSamples, int srcSamples, Buffer<short>& dstBuf, int dstOffsetSamples, int dstSamples, int channels);
			template void resample(const Buffer<short>& srcBuf, int srcOffsetSamples, int srcSamples, int srcChannels, Buffer<short>& dstBuf, int dstOffsetSamples, int dstSamples, int dstChannels);

		}
	}
}