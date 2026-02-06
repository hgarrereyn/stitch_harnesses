#include <Mesh.h>
#include <iostream>

using namespace mesh;

class DummyRadio : public Radio {
public:
  void begin() override {}
  int recvRaw(uint8_t*, int) override { return 0; }
  uint32_t getEstAirtimeFor(int len) override { return (uint32_t)(len * 10); }
  float packetScore(float, int) override { return 0.5f; }
  bool startSendRaw(const uint8_t*, int) override { return true; }
  bool isSendComplete() override { return true; }
  void onSendFinished() override {}
  void loop() override {}
  bool isInRecvMode() const override { return true; }
};

class DummyClock : public MillisecondClock {
  unsigned long t = 0;
public:
  unsigned long getMillis() override { return t += 10; }
};

class DummyRNG : public RNG {
public:
  void random(uint8_t* dest, size_t sz) override { for (size_t i=0;i<sz;i++) dest[i] = (uint8_t)(i*37); }
};

class DummyRTC : public RTCClock {
  uint32_t now = 1000;
public:
  uint32_t getCurrentTime() override { return now++; }
  void setCurrentTime(uint32_t t) override { now = t; }
};

class DummyPktMgr : public PacketManager {
public:
  Packet* allocNew() override { return nullptr; }
  void free(Packet*) override {}
  void queueOutbound(Packet*, uint8_t, uint32_t) override {}
  Packet* getNextOutbound(uint32_t) override { return nullptr; }
  int getOutboundCount(uint32_t) const override { return 0; }
  int getFreeCount() const override { return 0; }
  Packet* getOutboundByIdx(int) override { return nullptr; }
  Packet* removeOutboundByIdx(int) override { return nullptr; }
  void queueInbound(Packet*, uint32_t) override {}
  Packet* getNextInbound(uint32_t) override { return nullptr; }
};

class DummyTables : public MeshTables {
public:
  bool hasSeen(const Packet*) override { return false; }
  void clear(const Packet*) override {}
};

class MyMesh : public Mesh {
public:
  MyMesh(Radio& radio, MillisecondClock& ms, RNG& rng, RTCClock& rtc, PacketManager& mgr, MeshTables& tables)
    : Mesh(radio, ms, rng, rtc, mgr, tables) {}
};

int main(){
  DummyRadio radio; DummyClock ms; DummyRNG rng; DummyRTC rtc; DummyPktMgr mgr; DummyTables tables;
  MyMesh m(radio, ms, rng, rtc, mgr, tables);
  m.begin();
  m.loop();
  std::cout << "MeshCore basic setup OK\n";
  return 0;
}
