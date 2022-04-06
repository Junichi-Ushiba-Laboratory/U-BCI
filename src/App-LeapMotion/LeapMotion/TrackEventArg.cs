using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LslLeapMotion.LeapMotion
{
    /// <summary>
    /// Data class that will be the arguments of event handler, when tracking event triggered by LeapMotion
    /// </summary>
    class TrackEventArg : EventArgs
    {
        /// <summary>
        /// Acquired data from LeapMotion
        /// </summary>
        public PollingEvent Data;

        /// <summary>
        /// Constructors
        /// </summary>
        /// <param name="data">Unique data of tracking event</param>
        public TrackEventArg(PollingEvent data)
        {
            Data = data;
        }
    }
}
