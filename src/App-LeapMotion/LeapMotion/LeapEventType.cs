using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LslLeapMotion.LeapMotion
{
    /// <summary>
    /// Defined enum for LeapMotion events
    /// </summary>
    enum LeapEventType
    {
        eLeapEventType_None = 0,

        /**
         * A connection to the Leap Motion service has been established.
         * @since 3.0.0
         */
        Connection,

        /**
         * The connection to the Leap Motion service has been lost.
         * @since 3.0.0
         */
        ConnectionLost,

        /**
         * A device has been detected or plugged-in.
         * A device event is dispatched after a connection is established for any
         * devices already plugged in. (The system currently only supports one
         * streaming device at a time.)
         * @since 3.0.0
         */
        Device,

        /**
         * A device has failed.
         * Device failure could be caused by hardware failure, USB controller issues, or
         * other system instability. Note that unplugging a device generates an
         * eLeapEventType_DeviceLost event message, not a failure message.
         * @since 3.0.0
         */
        eLeapEventType_DeviceFailure,

        /**
         * A policy change has occurred.
         * This can be due to setting a policy with LeapSetPolicyFlags() or due to changing
         * or policy-related config settings, including images_mode.
         * (A user can also change these policies using the Leap Motion Control Panel.)
         * @since 3.0.0
         */
        eLeapEventType_Policy,

        /**
         * A tracking frame. The message contains the tracking data for the frame.
         * @since 3.0.0
         */
        Tracking = 0x100,

        /**
         * The request for an image has failed.
         * The message contains information about the failure. The client application
         * will not receive the requested image set.
         * @since 3.0.0
         */
        eLeapEventType_ImageRequestError,

        /**
        * The request for an image is complete.
        * The image data has been completely written to the application-provided
        * buffer.
        * @since 3.0.0
        */
        eLeapEventType_ImageComplete,

        /**
         * A system message. @since 3.0.0
         */
        LogEvent,

        /**
         * The device connection has been lost.
         *
         * This event is generally asserted when the device has been detached from the system, when the
         * connection to the service has been lost, or if the device is closed while streaming. Generally,
         * any event where the system can conclude no further frames will be received will result in this
         * message. The DeviceEvent field will be filled with the id of the formerly attached device.
         * @since 3.0.0
         */
        eLeapEventType_DeviceLost,

        /**
         * The asynchronous response to a call to LeapRequestConfigValue().
         * Contains the value of requested configuration item.
         * @since 3.0.0
         */
        eLeapEventType_ConfigResponse,

        /**
         * The asynchronous response to a call to LeapSaveConfigValue().
         * Reports whether the change succeeded or failed.
         * @since 3.0.0
         */
        eLeapEventType_ConfigChange,

        /**
         * Notification that a status change has been detected on an attached device
         *
         * @since 3.1.3
         */
        eLeapEventType_DeviceStatusChange,
        eLeapEventType_DroppedFrame,

        /**
         * Notification that an unrequested stereo image pair is available
         *
         * @since 4.0.0
         */
        eLeapEventType_Image,

        /**
         * Notification that point mapping has changed
         *
         * @since 4.0.0
         */
        eLeapEventType_PointMappingChange,

        /**
         * An array of system messages. @since 4.0.0
         */
        eLeapEventType_LogEvents,
        eLeapEventType_HeadPose
    }
}
