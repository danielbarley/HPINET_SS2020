//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
//

package ss2020_ueb06.Node;

simple Application {
    parameters:
        int FLIT_BYTES @unit(byte) = default(16byte);
        volatile double SEND_DELAY @unit(s) = default(uniform(1.0us, 25.0us));
        volatile int PKT_SIZE @unit(byte)= default(intuniform(32byte, 1504byte));
        int NODE_ID = default(0);
        string NODE_COUNT = default("1");
        bool ROUTE_TEST = default(false);

        // Signals
        @signal[sigHopCnt](type=long);
        @signal[sigPcktSize](type=long);
        @signal[sigE2ELatency](type=simtime_t);

        // Statistics
        @statistic[statHopCnt](source=sigHopCnt; record=histogram,stats,vector?);
        @statistic[statPcktSize](source=sigPcktSize; record=histogram,stats,vector?);
        @statistic[statE2ELatency](source=sigE2ELatency; record=histogram,stats,vector?);

    gates:
        inout data;
}
