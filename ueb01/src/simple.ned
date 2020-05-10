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

package packettest;

simple Simple
{
	parameters:
		int PKT_SIZE @unit(byte) = default(512Byte);
		double DATA_RATE @unit(bps) = default(1Gbps);
        int NUM_DISCARD = default(0);
        bool TIC = default(false);
    gates:
        inout data;
}
