#include "pch.h"
#include "GeneralModelShaderVS.h"
#if __has_include("GeneralModelShaderVS.g.cpp")
#include "GeneralModelShaderVS.g.cpp"
#endif

using namespace winrt;
using namespace Windows::UI::Xaml;

namespace winrt::NewTrainingFramework::implementation
{
    int32_t GeneralModelShaderVS::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void GeneralModelShaderVS::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }

    void GeneralModelShaderVS::ClickHandler(IInspectable const&, RoutedEventArgs const&)
    {
        Button().Content(box_value(L"Clicked"));
    }
}
