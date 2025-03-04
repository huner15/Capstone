﻿// This is the backend code for reading and writing

// Generated by ProtocolBuffer
// - a pure c# code generation implementation of protocol buffers
// Report bugs to: https://silentorbit.com/protobuf/

// DO NOT EDIT
// This file will be overwritten when CodeGenerator is run.
using System;
using System.IO;
using System.Text;
using System.Collections.Generic;

namespace Example
{
    [System.Serializable()]
    public partial class Msg
    {
        /// <summary>Helper: create a new instance to deserializing into</summary>
        public static Msg Deserialize(Stream stream)
        {
            Msg instance = new Msg();
            Deserialize(stream, instance);
            return instance;
        }

        /// <summary>Helper: create a new instance to deserializing into</summary>
        public static Msg DeserializeLengthDelimited(Stream stream)
        {
            Msg instance = new Msg();
            DeserializeLengthDelimited(stream, instance);
            return instance;
        }

        /// <summary>Helper: create a new instance to deserializing into</summary>
        public static Msg DeserializeLength(Stream stream, int length)
        {
            Msg instance = new Msg();
            DeserializeLength(stream, length, instance);
            return instance;
        }

        /// <summary>Helper: put the buffer into a MemoryStream and create a new instance to deserializing into</summary>
        public static Msg Deserialize(byte[] buffer)
        {
            Msg instance = new Msg();
            using (var ms = new MemoryStream(buffer))
                Deserialize(ms, instance);
            return instance;
        }

        /// <summary>Helper: put the buffer into a MemoryStream before deserializing</summary>
        public static Example.Msg Deserialize(byte[] buffer, Example.Msg instance)
        {
            using (var ms = new MemoryStream(buffer))
                Deserialize(ms, instance);
            return instance;
        }

        /// <summary>Takes the remaining content of the stream and deserialze it into the instance.</summary>
        public static Example.Msg Deserialize(Stream stream, Example.Msg instance)
        {
            while (true)
            {
                int keyByte = stream.ReadByte();
                if (keyByte == -1)
                    break;
                // Optimized reading of known fields with field ID < 16
                switch (keyByte)
                {
                    // Field 1 LengthDelimited
                    case 10:
                        instance.Name = global::SilentOrbit.ProtocolBuffers.ProtocolParser.ReadString(stream);
                        continue;
                    // Field 2 Varint
                    case 16:
                        instance.Age = (int)global::SilentOrbit.ProtocolBuffers.ProtocolParser.ReadUInt64(stream);
                        continue;
                }

                var key = global::SilentOrbit.ProtocolBuffers.ProtocolParser.ReadKey((byte)keyByte, stream);

                // Reading field ID > 16 and unknown field ID/wire type combinations
                switch (key.Field)
                {
                    case 0:
                        throw new global::SilentOrbit.ProtocolBuffers.ProtocolBufferException("Invalid field id: 0, something went wrong in the stream");
                    default:
                        global::SilentOrbit.ProtocolBuffers.ProtocolParser.SkipKey(stream, key);
                        break;
                }
            }

            return instance;
        }

        /// <summary>Read the VarInt length prefix and the given number of bytes from the stream and deserialze it into the instance.</summary>
        public static Example.Msg DeserializeLengthDelimited(Stream stream, Example.Msg instance)
        {
            long limit = global::SilentOrbit.ProtocolBuffers.ProtocolParser.ReadUInt32(stream);
            limit += stream.Position;
            while (true)
            {
                if (stream.Position >= limit)
                {
                    if (stream.Position == limit)
                        break;
                    else
                        throw new global::SilentOrbit.ProtocolBuffers.ProtocolBufferException("Read past max limit");
                }
                int keyByte = stream.ReadByte();
                if (keyByte == -1)
                    throw new System.IO.EndOfStreamException();
                // Optimized reading of known fields with field ID < 16
                switch (keyByte)
                {
                    // Field 1 LengthDelimited
                    case 10:
                        instance.Name = global::SilentOrbit.ProtocolBuffers.ProtocolParser.ReadString(stream);
                        continue;
                    // Field 2 Varint
                    case 16:
                        instance.Age = (int)global::SilentOrbit.ProtocolBuffers.ProtocolParser.ReadUInt64(stream);
                        continue;
                }

                var key = global::SilentOrbit.ProtocolBuffers.ProtocolParser.ReadKey((byte)keyByte, stream);

                // Reading field ID > 16 and unknown field ID/wire type combinations
                switch (key.Field)
                {
                    case 0:
                        throw new global::SilentOrbit.ProtocolBuffers.ProtocolBufferException("Invalid field id: 0, something went wrong in the stream");
                    default:
                        global::SilentOrbit.ProtocolBuffers.ProtocolParser.SkipKey(stream, key);
                        break;
                }
            }

            return instance;
        }

        /// <summary>Read the given number of bytes from the stream and deserialze it into the instance.</summary>
        public static Example.Msg DeserializeLength(Stream stream, int length, Example.Msg instance)
        {
            long limit = stream.Position + length;
            while (true)
            {
                if (stream.Position >= limit)
                {
                    if (stream.Position == limit)
                        break;
                    else
                        throw new global::SilentOrbit.ProtocolBuffers.ProtocolBufferException("Read past max limit");
                }
                int keyByte = stream.ReadByte();
                if (keyByte == -1)
                    throw new System.IO.EndOfStreamException();
                // Optimized reading of known fields with field ID < 16
                switch (keyByte)
                {
                    // Field 1 LengthDelimited
                    case 10:
                        instance.Name = global::SilentOrbit.ProtocolBuffers.ProtocolParser.ReadString(stream);
                        continue;
                    // Field 2 Varint
                    case 16:
                        instance.Age = (int)global::SilentOrbit.ProtocolBuffers.ProtocolParser.ReadUInt64(stream);
                        continue;
                }

                var key = global::SilentOrbit.ProtocolBuffers.ProtocolParser.ReadKey((byte)keyByte, stream);

                // Reading field ID > 16 and unknown field ID/wire type combinations
                switch (key.Field)
                {
                    case 0:
                        throw new global::SilentOrbit.ProtocolBuffers.ProtocolBufferException("Invalid field id: 0, something went wrong in the stream");
                    default:
                        global::SilentOrbit.ProtocolBuffers.ProtocolParser.SkipKey(stream, key);
                        break;
                }
            }

            return instance;
        }

        /// <summary>Serialize the instance into the stream</summary>
        public static void Serialize(Stream stream, Msg instance)
        {
            var msField = global::SilentOrbit.ProtocolBuffers.ProtocolParser.Stack.Pop();
            if (instance.Name == null)
                throw new ArgumentNullException("Name", "Required by proto specification.");
            // Key for field: 1, LengthDelimited
            stream.WriteByte(10);
            global::SilentOrbit.ProtocolBuffers.ProtocolParser.WriteBytes(stream, Encoding.UTF8.GetBytes(instance.Name));
            // Key for field: 2, Varint
            stream.WriteByte(16);
            global::SilentOrbit.ProtocolBuffers.ProtocolParser.WriteUInt64(stream,(ulong)instance.Age);
            global::SilentOrbit.ProtocolBuffers.ProtocolParser.Stack.Push(msField);
        }

        /// <summary>Helper: Serialize into a MemoryStream and return its byte array</summary>
        public static byte[] SerializeToBytes(Msg instance)
        {
            using (var ms = new MemoryStream())
            {
                Serialize(ms, instance);
                return ms.ToArray();
            }
        }
        /// <summary>Helper: Serialize with a varint length prefix</summary>
        public static void SerializeLengthDelimited(Stream stream, Msg instance)
        {
            var data = SerializeToBytes(instance);
            global::SilentOrbit.ProtocolBuffers.ProtocolParser.WriteUInt32(stream, (uint)data.Length);
            stream.Write(data, 0, data.Length);
        }
    }

}
