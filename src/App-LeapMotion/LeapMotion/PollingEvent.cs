using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace LslLeapMotion.LeapMotion
{
    /// <summary>
    /// Structures receiving from C++
    /// </summary>
    [StructLayout(LayoutKind.Sequential)]
    struct PollingEvent
    {
        // Event type
        public Int32 Type;

        // Frame ID
        public UInt64 FrameId;

        // Timestamp
        public UInt64 TimeStamp;

        // Tracking frame ID
        public UInt64 TrackingFrameId;

        // Number of hands
        public Int32 HandCount;

        // Frame rate
        public float FrameRate;

        // Right hand information
        public Int32 RightExist;

        public float RThumbX;
        public float RThumbY;
        public float RThumbZ;

        public float RIndexX;
        public float RIndexY;
        public float RIndexZ;

        public float RMiddleX;
        public float RMiddleY;
        public float RMiddleZ;

        public float RRingX;
        public float RRingY;
        public float RRingZ;

        public float RPinkyX;
        public float RPinkyY;
        public float RPinkyZ;

        public float RWristX;
        public float RWristY;
        public float RWristZ;

        // Left hand information
        public Int32 LeftExist;

        public float LThumbX;
        public float LThumbY;
        public float LThumbZ;

        public float LIndexX;
        public float LIndexY;
        public float LIndexZ;

        public float LMiddleX;
        public float LMiddleY;
        public float LMiddleZ;

        public float LRingX;
        public float LRingY;
        public float LRingZ;

        public float LPinkyX;
        public float LPinkyY;
        public float LPinkyZ;

        public float LWristX;
        public float LWristY;
        public float LWristZ;
    }
}
