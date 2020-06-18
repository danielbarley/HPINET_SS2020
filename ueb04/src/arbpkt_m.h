//
// Generated file, do not edit! Created by nedtool 5.6 from arbpkt.msg.
//

#ifndef __ARBPKT_M_H
#define __ARBPKT_M_H

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wreserved-id-macro"
#endif
#include <omnetpp.h>

// nedtool version check
#define MSGC_VERSION 0x0506
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of nedtool: 'make clean' should help.
#endif



/**
 * Class generated from <tt>arbpkt.msg:1</tt> by nedtool.
 * <pre>
 * packet Arbpkt
 * {
 *     unsigned int type;
 *     int sourcePort;
 *     int targetOutport;
 * }
 * </pre>
 */
class Arbpkt : public ::omnetpp::cPacket
{
  protected:
    unsigned int type;
    int sourcePort;
    int targetOutport;

  private:
    void copy(const Arbpkt& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const Arbpkt&);

  public:
    Arbpkt(const char *name=nullptr, short kind=0);
    Arbpkt(const Arbpkt& other);
    virtual ~Arbpkt();
    Arbpkt& operator=(const Arbpkt& other);
    virtual Arbpkt *dup() const override {return new Arbpkt(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual unsigned int getType() const;
    virtual void setType(unsigned int type);
    virtual int getSourcePort() const;
    virtual void setSourcePort(int sourcePort);
    virtual int getTargetOutport() const;
    virtual void setTargetOutport(int targetOutport);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const Arbpkt& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, Arbpkt& obj) {obj.parsimUnpack(b);}


#endif // ifndef __ARBPKT_M_H

