#pragma once
#include <Audioclient.h>

//�����ʵĵ�����ô��ʵ�֣�
// TODO: iaudioclockadjustment implementation for adjusting sample rate

template<typename T>
struct duplicate
{
	//ĳ�����͵Ĵ���
    T* proxy;
	//ָ��ǰ�ڵ㣬Ӧ����β�ڵ㿩
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
		//ָ��ĵ�ַ
        duplicate** item = &this->next;
        while(*item != NULL)
            item = &(*item)->next;
		//��ַ��ֵ
        *item = new duplicate(proxy);
    }
};

//��Ƶ�ͻ��ˡ���Ƶ��Ⱦ�ͻ��ˡ���Ƶ����
typedef duplicate<IAudioClient> iaudioclient_duplicate;
typedef duplicate<IAudioRenderClient> iaudiorenderclient_duplicate;
typedef duplicate<IAudioStreamVolume> iaudiostreamvolume_duplicate;

void patch_iaudioclient(IAudioClient* host, LPGUID session_guid);
//����һ����Ƶ�ͻ���
iaudioclient_duplicate* get_duplicate(IAudioClient* host);

void patch_iaudiorenderclient(IAudioRenderClient* host, WORD block_align);
iaudiorenderclient_duplicate* get_duplicate(IAudioRenderClient* host);

void patch_iaudiostreamvolume(IAudioStreamVolume* host);
iaudiostreamvolume_duplicate* get_duplicate(IAudioStreamVolume* host);