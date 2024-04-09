#pragma once
#include "MinGWComponent/ComponentClass.g.h"

namespace winrt::MinGWComponent::implementation
{
    struct ComponentClass : ComponentClassT<ComponentClass>
    {
        ComponentClass() = default;

        int32_t IntProperty();
        int32_t Add(int32_t a, int32_t b);
        winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Storage::Streams::IRandomAccessStream> DownloadFileAsync(hstring url);
    };
}
namespace winrt::MinGWComponent::factory_implementation
{
    struct ComponentClass : ComponentClassT<ComponentClass, implementation::ComponentClass>
    {
    };
}
