using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LslLeapMotion.LeapMotion
{
    /// <summary>
    /// Arguments of event handler when the connection lost
    /// </summary>
    class LostConnectionEventArg : EventArgs
    {
        /// <summary>
        /// Message
        /// </summary>
        public readonly string Message;

        /// <summary>
        /// Constructors
        /// </summary>
        /// <param name="message"></param>
        public LostConnectionEventArg(string message)
        {
            Message = message;
        }
    }
}
