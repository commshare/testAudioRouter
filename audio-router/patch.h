#pragma once
#include <Audioclient.h>

//采样率的调整还么有实现？
// TODO: iaudioclockadjustment implementation for adjusting sample rate

template<typename T>
struct duplicate
{
	//某种类型的代理
    T* proxy;
	//指向当前节点，应该是尾节点咯
    duplicate* next;

    explicit duplicate(T* proxy) : proxy(proxy), next(NULL) {}
    ~duplicate() 
    {
        if(this->proxy) 
            this->proxy->Release();
        delete this->next;
    }
    void add(T* proxy) 
    {
		//指针的地址
        duplicate** item = &this->next;
        while(*item != NULL)
            item = &(*item)->next;
		//地址赋值
        *item = new duplicate(proxy);
    }
};

//音频客户端、音频渲染客户端、音频音量
typedef duplicate<IAudioClient> iaudioclient_duplicate;
typedef duplicate<IAudioRenderClient> iaudiorenderclient_duplicate;
typedef duplicate<IAudioStreamVolume> iaudiostreamvolume_duplicate;

void patch_iaudioclient(IAudioClient* host, LPGUID session_guid);
//复制一个音频客户端
iaudioclient_duplicate* get_duplicate(IAudioClient* host);

void patch_iaudiorenderclient(IAudioRenderClient* host, WORD block_align);
iaudiorenderclient_duplicate* get_duplicate(IAudioRenderClient* host);

void patch_iaudiostreamvolume(IAudioStreamVolume* host);
iaudiostreamvolume_duplicate* get_duplicate(IAudioStreamVolume* host);