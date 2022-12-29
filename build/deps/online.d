build/objs/online.o: src/online.cpp photon/LoadBalancing-cpp/inc/Client.h \
  photon/LoadBalancing-cpp/inc/ClientConstructOptions.h \
  photon/Common-cpp/inc/Enums/SerializationProtocol.h \
  photon/Common-cpp/inc/defines.h \
  photon/Common-cpp/inc/platform_definition.h \
  photon/Common-cpp/inc/Helpers/debug_assert.h \
  photon/Photon-cpp/inc/Enums/ConnectionProtocol.h \
  photon/Common-cpp/inc/Common.h photon/Common-cpp/inc/ANSIString.h \
  photon/Common-cpp/inc/BaseCharString.h photon/Common-cpp/inc/Base.h \
  photon/Common-cpp/inc/LoggingBase.h photon/Common-cpp/inc/Logger.h \
  photon/Common-cpp/inc/BaseListener.h \
  photon/Common-cpp/inc/Enums/DebugLevel.h \
  photon/Common-cpp/inc/JString.h photon/Common-cpp/inc/ToString.h \
  photon/Common-cpp/inc/LogFormatOptions.h \
  photon/Common-cpp/inc/Deserializer.h photon/Common-cpp/inc/Object.h \
  photon/Common-cpp/inc/JTime.h \
  photon/Common-cpp/inc/Containers/Dictionary.h \
  photon/Common-cpp/inc/Containers/DictionaryBase.h \
  photon/Common-cpp/inc/Containers/GenericAssociativeContainerBase.h \
  photon/Common-cpp/inc/Containers/JVector.h \
  photon/Common-cpp/inc/Containers/SequenceContainer.h \
  photon/Common-cpp/inc/Helpers/Stringification/Stringifier.h \
  photon/Common-cpp/inc/Helpers/Stringification/StringifierImplementation.h \
  photon/Common-cpp/inc/Helpers/Stringification/ToStringImplementation.h \
  photon/Common-cpp/inc/Helpers/Stringification/ObjectToStringConverter.h \
  photon/Common-cpp/inc/Helpers/Stringification/ObjectToStringConverterBase.h \
  photon/Common-cpp/inc/Helpers/ElementAccessor.h \
  photon/Common-cpp/inc/Helpers/SmartPointers/SmartPointerBase.h \
  photon/Common-cpp/inc/MemoryManagement/Allocate.h \
  photon/Common-cpp/inc/MemoryManagement/AllocatorInterface.h \
  photon/Common-cpp/inc/Helpers/TypeTraits/IsDerivedFrom.h \
  photon/Common-cpp/inc/Helpers/Stringification/PrimitiveToStringConverter.h \
  photon/Common-cpp/inc/Helpers/Stringification/PrimitiveToStringConverterBase.h \
  photon/Common-cpp/inc/Helpers/TypeTraits/IsPrimitiveType.h \
  photon/Common-cpp/inc/Helpers/TypeTraits/IsClass.h \
  photon/Common-cpp/inc/Helpers/TypeTraits/IsUnion.h \
  photon/Common-cpp/inc/Helpers/TypeTraits/RemovePointer.h \
  photon/Common-cpp/inc/MemoryManagement/Internal/Interface.h \
  photon/Common-cpp/inc/Containers/Hashtable.h \
  photon/Common-cpp/inc/Containers/AssociativeContainerBase.h \
  photon/Common-cpp/inc/Helpers/KeyToObject.h \
  photon/Common-cpp/inc/KeyObject.h \
  photon/Common-cpp/inc/Helpers/ConfirmAllowedKey.h \
  photon/Common-cpp/inc/Helpers/CompileTimeAssertTrue.h \
  photon/Common-cpp/inc/Enums/TypeCode.h \
  photon/Common-cpp/inc/Helpers/ValueToObject.h \
  photon/Common-cpp/inc/ValueObject.h \
  photon/Common-cpp/inc/Helpers/ConfirmAllowed.h \
  photon/Common-cpp/inc/CustomType.h \
  photon/Common-cpp/inc/CustomTypeBase.h \
  photon/Common-cpp/inc/Helpers/CustomTypeCallbackWrapper.h \
  photon/Common-cpp/inc/Helpers/CustomTypeFactory.h \
  photon/Common-cpp/inc/Helpers/TypeName.h \
  photon/Common-cpp/inc/Helpers/TypeTraits/EnableIf.h \
  photon/Common-cpp/inc/Helpers/TypeTraits/IsSame.h \
  photon/Common-cpp/inc/Containers/JArray.h \
  photon/Common-cpp/inc/Containers/JDictionary.h \
  photon/Common-cpp/inc/Containers/GenericAssociativeContainer.h \
  photon/Common-cpp/inc/Containers/JHashtable.h \
  photon/Common-cpp/inc/Containers/AssociativeContainer.h \
  photon/Common-cpp/inc/JObject.h \
  photon/Common-cpp/inc/Helpers/SmartPointers/UniquePointer.h \
  photon/Common-cpp/inc/Helpers/SmartPointers/UniquePointerBase.h \
  photon/Common-cpp/inc/Helpers/SmartPointers/SmartPointerInterface.h \
  photon/Common-cpp/inc/Helpers/TypeID.h \
  photon/Common-cpp/inc/Containers/JHashSet.h \
  photon/Common-cpp/inc/Containers/JLinkedList.h \
  photon/Common-cpp/inc/Containers/JList.h \
  photon/Common-cpp/inc/Containers/JQueue.h \
  photon/Common-cpp/inc/Containers/JSortedList.h \
  photon/Common-cpp/inc/Containers/JStack.h \
  photon/Common-cpp/inc/Helpers/AutoResetEvent.h \
  photon/Common-cpp/inc/Helpers/Dispatcher.h \
  photon/Common-cpp/inc/Helpers/Callback.h \
  photon/Common-cpp/inc/Helpers/CallbackBase.h \
  photon/Common-cpp/inc/Helpers/Message.h \
  photon/Common-cpp/inc/Helpers/SmartPointers/SharedPointer.h \
  photon/Common-cpp/inc/Helpers/SmartPointers/SharedPointerBase.h \
  photon/Common-cpp/inc/Helpers/Lockable.h \
  photon/Common-cpp/inc/Helpers/LockableNonAssignable.h \
  photon/Common-cpp/inc/Helpers/Lockguard.h \
  photon/Common-cpp/inc/Helpers/Spinlock.h \
  photon/Common-cpp/inc/Helpers/Thread.h \
  photon/Common-cpp/inc/platformLayer.h photon/Common-cpp/inc/porting.h \
  photon/Common-cpp/inc/Helpers/MathHelper.h \
  photon/Common-cpp/inc/Helpers/RecursivelyLockable.h \
  photon/Common-cpp/inc/Helpers/RecursivelyLockableNonAssignable.h \
  photon/Common-cpp/inc/Helpers/Retainable.h \
  photon/Common-cpp/inc/Helpers/Serialization/DeserializerImplementationProtocol16.h \
  photon/Common-cpp/inc/Helpers/ArrayLengthType.h \
  photon/Common-cpp/inc/Helpers/Serialization/DeserializerImplementation.h \
  photon/Common-cpp/inc/Helpers/TypeTraits/Conditional.h \
  photon/Common-cpp/inc/Helpers/TypeTraits/IsArithmetic.h \
  photon/Common-cpp/inc/Helpers/TypeTraits/IsFloatingPoint.h \
  photon/Common-cpp/inc/Helpers/TypeTraits/IsIntegral.h \
  photon/Common-cpp/inc/Helpers/Serialization/TypeCode/IsValid1DArrayElement.h \
  photon/Common-cpp/inc/Helpers/Serialization/TypeCode/IsValid.h \
  photon/Common-cpp/inc/Helpers/Serialization/TypeCode/TypeForCode.h \
  photon/Common-cpp/inc/Helpers/Serialization/DeserializerImplementationProtocol18.h \
  photon/Common-cpp/inc/Helpers/Serialization/TypeCode18/CodeForType.h \
  photon/Common-cpp/inc/Helpers/Serialization/TypeCode18/TypeCode18.h \
  photon/Common-cpp/inc/Helpers/Serialization/TypeCode18/Is1DArray.h \
  photon/Common-cpp/inc/Helpers/Serialization/TypeCode18/IsArray.h \
  photon/Common-cpp/inc/Helpers/Serialization/TypeCode18/IsCustom.h \
  photon/Common-cpp/inc/Helpers/Serialization/TypeCode18/IsValid.h \
  photon/Common-cpp/inc/Helpers/Serialization/TypeCode18/TypeForCode.h \
  photon/Common-cpp/inc/Helpers/Serialization/TypeCode18/ObjectTypeCodeForCode.h \
  photon/Common-cpp/inc/Helpers/Serialization/TypeCode18/UnsignedCode.h \
  photon/Common-cpp/inc/Helpers/TypeTraits/MakeSigned.h \
  photon/Common-cpp/inc/Helpers/Serialization/SerializerImplementationSource.h \
  photon/Common-cpp/inc/Helpers/Serialization/SerializerImplementationProtocol16.h \
  photon/Common-cpp/inc/Helpers/Serialization/SerializerImplementation.h \
  photon/Common-cpp/inc/Helpers/Data.h \
  photon/Common-cpp/inc/Helpers/Serialization/SerializerImplementationProtocol18.h \
  photon/Common-cpp/inc/Helpers/Serialization/TypeCode18/CodeZero.h \
  photon/Common-cpp/inc/Helpers/Serialization/TypeCode18/IntegerTypeCode.h \
  photon/Common-cpp/inc/Helpers/TypeTraits/MakeUnsigned.h \
  photon/Common-cpp/inc/Helpers/TypeTraits/IsCompound.h \
  photon/Common-cpp/inc/Helpers/TypeTraits/IsFundamental.h \
  photon/Common-cpp/inc/Helpers/TypeTraits/IsVoid.h \
  photon/Common-cpp/inc/Helpers/TypeTraits/IsObject.h \
  photon/Common-cpp/inc/Helpers/TypeTraits/IsScalar.h \
  photon/Common-cpp/inc/Helpers/TypeTraits/IsEnum.h \
  photon/Common-cpp/inc/Helpers/TypeTraits/IsArray.h \
  photon/Common-cpp/inc/Helpers/TypeTraits/IsFunction.h \
  photon/Common-cpp/inc/Helpers/TypeTraits/IsReference.h \
  photon/Common-cpp/inc/Helpers/TypeTraits/IsMemberPointer.h \
  photon/Common-cpp/inc/Helpers/TypeTraits/IsPointer.h \
  photon/Common-cpp/inc/Helpers/TypeTraits/RemoveConst.h \
  photon/Common-cpp/inc/Helpers/SpinLockable.h \
  photon/Common-cpp/inc/Helpers/SpinLockableNonAssignable.h \
  photon/Common-cpp/inc/Helpers/Stringifyable.h \
  photon/Common-cpp/inc/Helpers/StringifyableNonAssignable.h \
  photon/Common-cpp/inc/Nullable.h photon/Common-cpp/inc/Serializer.h \
  photon/Common-cpp/inc/ToStringDefaultImplementation.h \
  photon/Common-cpp/inc/UTF8String.h \
  photon/LoadBalancing-cpp/inc/Enums/RegionSelectionMode.h \
  photon/LoadBalancing-cpp/inc/ConnectOptions.h \
  photon/LoadBalancing-cpp/inc/AuthenticationValues.h \
  photon/LoadBalancing-cpp/inc/Enums/CustomAuthenticationType.h \
  photon/LoadBalancing-cpp/inc/Enums/ServerType.h \
  photon/LoadBalancing-cpp/inc/Enums/DisconnectCause.h \
  photon/LoadBalancing-cpp/inc/Enums/ErrorCode.h \
  photon/LoadBalancing-cpp/inc/Enums/PeerStates.h \
  photon/LoadBalancing-cpp/inc/FriendInfo.h \
  photon/LoadBalancing-cpp/inc/Listener.h \
  photon/Photon-cpp/inc/OperationResponse.h \
  photon/LoadBalancing-cpp/inc/LobbyStatsResponse.h \
  photon/LoadBalancing-cpp/inc/Enums/LobbyType.h \
  photon/LoadBalancing-cpp/inc/MutablePlayer.h \
  photon/LoadBalancing-cpp/inc/Player.h \
  photon/LoadBalancing-cpp/inc/Internal/PlayerFactory.h \
  photon/LoadBalancing-cpp/inc/Internal/PlayerMutableRoomPointerSetter.h \
  photon/LoadBalancing-cpp/inc/Internal/PlayerPropertiesCacher.h \
  photon/LoadBalancing-cpp/inc/Internal/MutablePlayerFactory.h \
  photon/LoadBalancing-cpp/inc/WebFlags.h \
  photon/LoadBalancing-cpp/inc/MutableRoom.h \
  photon/LoadBalancing-cpp/inc/Peer.h photon/Photon-cpp/inc/PhotonPeer.h \
  photon/Photon-cpp/inc/PhotonListener.h \
  photon/Photon-cpp/inc/EventData.h \
  photon/Photon-cpp/inc/OperationRequest.h \
  photon/Photon-cpp/inc/TrafficStats.h \
  photon/Photon-cpp/inc/TrafficStatsGameLevel.h \
  photon/Photon-cpp/inc/Version.h \
  photon/Photon-cpp/inc/Enums/ErrorCode.h \
  photon/Photon-cpp/inc/Enums/NetworkPort.h \
  photon/Photon-cpp/inc/Enums/PeerState.h \
  photon/Photon-cpp/inc/Enums/StatusCode.h \
  photon/LoadBalancing-cpp/inc/Enums/MatchmakingMode.h \
  photon/LoadBalancing-cpp/inc/LobbyStatsRequest.h \
  photon/LoadBalancing-cpp/inc/RaiseEventOptions.h \
  photon/Photon-cpp/inc/Enums/EventCache.h \
  photon/Photon-cpp/inc/Enums/ReceiverGroup.h \
  photon/LoadBalancing-cpp/inc/RoomOptions.h \
  photon/LoadBalancing-cpp/inc/Enums/DirectMode.h \
  photon/LoadBalancing-cpp/inc/Room.h \
  photon/LoadBalancing-cpp/inc/Internal/RoomFactory.h \
  photon/LoadBalancing-cpp/inc/Internal/RoomPropertiesCacher.h \
  photon/LoadBalancing-cpp/inc/Internal/MutableRoomFactory.h \
  photon/LoadBalancing-cpp/inc/Internal/PlayerPropertiesUpdateInformant.h \
  photon/LoadBalancing-cpp/inc/SendDirectOptions.h

photon/LoadBalancing-cpp/inc/Client.h:

photon/LoadBalancing-cpp/inc/ClientConstructOptions.h:

photon/Common-cpp/inc/Enums/SerializationProtocol.h:

photon/Common-cpp/inc/defines.h:

photon/Common-cpp/inc/platform_definition.h:

photon/Common-cpp/inc/Helpers/debug_assert.h:

photon/Photon-cpp/inc/Enums/ConnectionProtocol.h:

photon/Common-cpp/inc/Common.h:

photon/Common-cpp/inc/ANSIString.h:

photon/Common-cpp/inc/BaseCharString.h:

photon/Common-cpp/inc/Base.h:

photon/Common-cpp/inc/LoggingBase.h:

photon/Common-cpp/inc/Logger.h:

photon/Common-cpp/inc/BaseListener.h:

photon/Common-cpp/inc/Enums/DebugLevel.h:

photon/Common-cpp/inc/JString.h:

photon/Common-cpp/inc/ToString.h:

photon/Common-cpp/inc/LogFormatOptions.h:

photon/Common-cpp/inc/Deserializer.h:

photon/Common-cpp/inc/Object.h:

photon/Common-cpp/inc/JTime.h:

photon/Common-cpp/inc/Containers/Dictionary.h:

photon/Common-cpp/inc/Containers/DictionaryBase.h:

photon/Common-cpp/inc/Containers/GenericAssociativeContainerBase.h:

photon/Common-cpp/inc/Containers/JVector.h:

photon/Common-cpp/inc/Containers/SequenceContainer.h:

photon/Common-cpp/inc/Helpers/Stringification/Stringifier.h:

photon/Common-cpp/inc/Helpers/Stringification/StringifierImplementation.h:

photon/Common-cpp/inc/Helpers/Stringification/ToStringImplementation.h:

photon/Common-cpp/inc/Helpers/Stringification/ObjectToStringConverter.h:

photon/Common-cpp/inc/Helpers/Stringification/ObjectToStringConverterBase.h:

photon/Common-cpp/inc/Helpers/ElementAccessor.h:

photon/Common-cpp/inc/Helpers/SmartPointers/SmartPointerBase.h:

photon/Common-cpp/inc/MemoryManagement/Allocate.h:

photon/Common-cpp/inc/MemoryManagement/AllocatorInterface.h:

photon/Common-cpp/inc/Helpers/TypeTraits/IsDerivedFrom.h:

photon/Common-cpp/inc/Helpers/Stringification/PrimitiveToStringConverter.h:

photon/Common-cpp/inc/Helpers/Stringification/PrimitiveToStringConverterBase.h:

photon/Common-cpp/inc/Helpers/TypeTraits/IsPrimitiveType.h:

photon/Common-cpp/inc/Helpers/TypeTraits/IsClass.h:

photon/Common-cpp/inc/Helpers/TypeTraits/IsUnion.h:

photon/Common-cpp/inc/Helpers/TypeTraits/RemovePointer.h:

photon/Common-cpp/inc/MemoryManagement/Internal/Interface.h:

photon/Common-cpp/inc/Containers/Hashtable.h:

photon/Common-cpp/inc/Containers/AssociativeContainerBase.h:

photon/Common-cpp/inc/Helpers/KeyToObject.h:

photon/Common-cpp/inc/KeyObject.h:

photon/Common-cpp/inc/Helpers/ConfirmAllowedKey.h:

photon/Common-cpp/inc/Helpers/CompileTimeAssertTrue.h:

photon/Common-cpp/inc/Enums/TypeCode.h:

photon/Common-cpp/inc/Helpers/ValueToObject.h:

photon/Common-cpp/inc/ValueObject.h:

photon/Common-cpp/inc/Helpers/ConfirmAllowed.h:

photon/Common-cpp/inc/CustomType.h:

photon/Common-cpp/inc/CustomTypeBase.h:

photon/Common-cpp/inc/Helpers/CustomTypeCallbackWrapper.h:

photon/Common-cpp/inc/Helpers/CustomTypeFactory.h:

photon/Common-cpp/inc/Helpers/TypeName.h:

photon/Common-cpp/inc/Helpers/TypeTraits/EnableIf.h:

photon/Common-cpp/inc/Helpers/TypeTraits/IsSame.h:

photon/Common-cpp/inc/Containers/JArray.h:

photon/Common-cpp/inc/Containers/JDictionary.h:

photon/Common-cpp/inc/Containers/GenericAssociativeContainer.h:

photon/Common-cpp/inc/Containers/JHashtable.h:

photon/Common-cpp/inc/Containers/AssociativeContainer.h:

photon/Common-cpp/inc/JObject.h:

photon/Common-cpp/inc/Helpers/SmartPointers/UniquePointer.h:

photon/Common-cpp/inc/Helpers/SmartPointers/UniquePointerBase.h:

photon/Common-cpp/inc/Helpers/SmartPointers/SmartPointerInterface.h:

photon/Common-cpp/inc/Helpers/TypeID.h:

photon/Common-cpp/inc/Containers/JHashSet.h:

photon/Common-cpp/inc/Containers/JLinkedList.h:

photon/Common-cpp/inc/Containers/JList.h:

photon/Common-cpp/inc/Containers/JQueue.h:

photon/Common-cpp/inc/Containers/JSortedList.h:

photon/Common-cpp/inc/Containers/JStack.h:

photon/Common-cpp/inc/Helpers/AutoResetEvent.h:

photon/Common-cpp/inc/Helpers/Dispatcher.h:

photon/Common-cpp/inc/Helpers/Callback.h:

photon/Common-cpp/inc/Helpers/CallbackBase.h:

photon/Common-cpp/inc/Helpers/Message.h:

photon/Common-cpp/inc/Helpers/SmartPointers/SharedPointer.h:

photon/Common-cpp/inc/Helpers/SmartPointers/SharedPointerBase.h:

photon/Common-cpp/inc/Helpers/Lockable.h:

photon/Common-cpp/inc/Helpers/LockableNonAssignable.h:

photon/Common-cpp/inc/Helpers/Lockguard.h:

photon/Common-cpp/inc/Helpers/Spinlock.h:

photon/Common-cpp/inc/Helpers/Thread.h:

photon/Common-cpp/inc/platformLayer.h:

photon/Common-cpp/inc/porting.h:

photon/Common-cpp/inc/Helpers/MathHelper.h:

photon/Common-cpp/inc/Helpers/RecursivelyLockable.h:

photon/Common-cpp/inc/Helpers/RecursivelyLockableNonAssignable.h:

photon/Common-cpp/inc/Helpers/Retainable.h:

photon/Common-cpp/inc/Helpers/Serialization/DeserializerImplementationProtocol16.h:

photon/Common-cpp/inc/Helpers/ArrayLengthType.h:

photon/Common-cpp/inc/Helpers/Serialization/DeserializerImplementation.h:

photon/Common-cpp/inc/Helpers/TypeTraits/Conditional.h:

photon/Common-cpp/inc/Helpers/TypeTraits/IsArithmetic.h:

photon/Common-cpp/inc/Helpers/TypeTraits/IsFloatingPoint.h:

photon/Common-cpp/inc/Helpers/TypeTraits/IsIntegral.h:

photon/Common-cpp/inc/Helpers/Serialization/TypeCode/IsValid1DArrayElement.h:

photon/Common-cpp/inc/Helpers/Serialization/TypeCode/IsValid.h:

photon/Common-cpp/inc/Helpers/Serialization/TypeCode/TypeForCode.h:

photon/Common-cpp/inc/Helpers/Serialization/DeserializerImplementationProtocol18.h:

photon/Common-cpp/inc/Helpers/Serialization/TypeCode18/CodeForType.h:

photon/Common-cpp/inc/Helpers/Serialization/TypeCode18/TypeCode18.h:

photon/Common-cpp/inc/Helpers/Serialization/TypeCode18/Is1DArray.h:

photon/Common-cpp/inc/Helpers/Serialization/TypeCode18/IsArray.h:

photon/Common-cpp/inc/Helpers/Serialization/TypeCode18/IsCustom.h:

photon/Common-cpp/inc/Helpers/Serialization/TypeCode18/IsValid.h:

photon/Common-cpp/inc/Helpers/Serialization/TypeCode18/TypeForCode.h:

photon/Common-cpp/inc/Helpers/Serialization/TypeCode18/ObjectTypeCodeForCode.h:

photon/Common-cpp/inc/Helpers/Serialization/TypeCode18/UnsignedCode.h:

photon/Common-cpp/inc/Helpers/TypeTraits/MakeSigned.h:

photon/Common-cpp/inc/Helpers/Serialization/SerializerImplementationSource.h:

photon/Common-cpp/inc/Helpers/Serialization/SerializerImplementationProtocol16.h:

photon/Common-cpp/inc/Helpers/Serialization/SerializerImplementation.h:

photon/Common-cpp/inc/Helpers/Data.h:

photon/Common-cpp/inc/Helpers/Serialization/SerializerImplementationProtocol18.h:

photon/Common-cpp/inc/Helpers/Serialization/TypeCode18/CodeZero.h:

photon/Common-cpp/inc/Helpers/Serialization/TypeCode18/IntegerTypeCode.h:

photon/Common-cpp/inc/Helpers/TypeTraits/MakeUnsigned.h:

photon/Common-cpp/inc/Helpers/TypeTraits/IsCompound.h:

photon/Common-cpp/inc/Helpers/TypeTraits/IsFundamental.h:

photon/Common-cpp/inc/Helpers/TypeTraits/IsVoid.h:

photon/Common-cpp/inc/Helpers/TypeTraits/IsObject.h:

photon/Common-cpp/inc/Helpers/TypeTraits/IsScalar.h:

photon/Common-cpp/inc/Helpers/TypeTraits/IsEnum.h:

photon/Common-cpp/inc/Helpers/TypeTraits/IsArray.h:

photon/Common-cpp/inc/Helpers/TypeTraits/IsFunction.h:

photon/Common-cpp/inc/Helpers/TypeTraits/IsReference.h:

photon/Common-cpp/inc/Helpers/TypeTraits/IsMemberPointer.h:

photon/Common-cpp/inc/Helpers/TypeTraits/IsPointer.h:

photon/Common-cpp/inc/Helpers/TypeTraits/RemoveConst.h:

photon/Common-cpp/inc/Helpers/SpinLockable.h:

photon/Common-cpp/inc/Helpers/SpinLockableNonAssignable.h:

photon/Common-cpp/inc/Helpers/Stringifyable.h:

photon/Common-cpp/inc/Helpers/StringifyableNonAssignable.h:

photon/Common-cpp/inc/Nullable.h:

photon/Common-cpp/inc/Serializer.h:

photon/Common-cpp/inc/ToStringDefaultImplementation.h:

photon/Common-cpp/inc/UTF8String.h:

photon/LoadBalancing-cpp/inc/Enums/RegionSelectionMode.h:

photon/LoadBalancing-cpp/inc/ConnectOptions.h:

photon/LoadBalancing-cpp/inc/AuthenticationValues.h:

photon/LoadBalancing-cpp/inc/Enums/CustomAuthenticationType.h:

photon/LoadBalancing-cpp/inc/Enums/ServerType.h:

photon/LoadBalancing-cpp/inc/Enums/DisconnectCause.h:

photon/LoadBalancing-cpp/inc/Enums/ErrorCode.h:

photon/LoadBalancing-cpp/inc/Enums/PeerStates.h:

photon/LoadBalancing-cpp/inc/FriendInfo.h:

photon/LoadBalancing-cpp/inc/Listener.h:

photon/Photon-cpp/inc/OperationResponse.h:

photon/LoadBalancing-cpp/inc/LobbyStatsResponse.h:

photon/LoadBalancing-cpp/inc/Enums/LobbyType.h:

photon/LoadBalancing-cpp/inc/MutablePlayer.h:

photon/LoadBalancing-cpp/inc/Player.h:

photon/LoadBalancing-cpp/inc/Internal/PlayerFactory.h:

photon/LoadBalancing-cpp/inc/Internal/PlayerMutableRoomPointerSetter.h:

photon/LoadBalancing-cpp/inc/Internal/PlayerPropertiesCacher.h:

photon/LoadBalancing-cpp/inc/Internal/MutablePlayerFactory.h:

photon/LoadBalancing-cpp/inc/WebFlags.h:

photon/LoadBalancing-cpp/inc/MutableRoom.h:

photon/LoadBalancing-cpp/inc/Peer.h:

photon/Photon-cpp/inc/PhotonPeer.h:

photon/Photon-cpp/inc/PhotonListener.h:

photon/Photon-cpp/inc/EventData.h:

photon/Photon-cpp/inc/OperationRequest.h:

photon/Photon-cpp/inc/TrafficStats.h:

photon/Photon-cpp/inc/TrafficStatsGameLevel.h:

photon/Photon-cpp/inc/Version.h:

photon/Photon-cpp/inc/Enums/ErrorCode.h:

photon/Photon-cpp/inc/Enums/NetworkPort.h:

photon/Photon-cpp/inc/Enums/PeerState.h:

photon/Photon-cpp/inc/Enums/StatusCode.h:

photon/LoadBalancing-cpp/inc/Enums/MatchmakingMode.h:

photon/LoadBalancing-cpp/inc/LobbyStatsRequest.h:

photon/LoadBalancing-cpp/inc/RaiseEventOptions.h:

photon/Photon-cpp/inc/Enums/EventCache.h:

photon/Photon-cpp/inc/Enums/ReceiverGroup.h:

photon/LoadBalancing-cpp/inc/RoomOptions.h:

photon/LoadBalancing-cpp/inc/Enums/DirectMode.h:

photon/LoadBalancing-cpp/inc/Room.h:

photon/LoadBalancing-cpp/inc/Internal/RoomFactory.h:

photon/LoadBalancing-cpp/inc/Internal/RoomPropertiesCacher.h:

photon/LoadBalancing-cpp/inc/Internal/MutableRoomFactory.h:

photon/LoadBalancing-cpp/inc/Internal/PlayerPropertiesUpdateInformant.h:

photon/LoadBalancing-cpp/inc/SendDirectOptions.h:
