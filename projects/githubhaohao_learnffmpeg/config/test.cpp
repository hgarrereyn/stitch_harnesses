#include <learnffmpeg/ThreadSafeQueue.h>
#include <learnffmpeg/Decoder.h>
#include <iostream>
#include <memory>

class DummyDecoder : public Decoder {
public:
    void Start() override { state = 1; }
    void Pause() override { state = 2; }
    void Stop() override { state = 0; }
    float GetDuration() override { return 0.0f; }
    void SeekToPosition(float) override {}
    float GetCurrentPosition() override { return 0.0f; }
    void SetMessageCallback(void*, MessageCallback) override {}
private:
    int state = 0;
};

int main(){
    ThreadSafeQueue<int*> q;
    int a = 42;
    q.Push(&a);
    auto p = q.Pop();
    if(p && *p == 42){
        std::cout << "OK\n";
    }
    DummyDecoder d; d.Start(); d.Pause(); d.Stop();
    return 0;
}
