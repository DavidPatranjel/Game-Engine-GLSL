#pragma once

#include "GeneralModelShaderVS.g.h"

namespace winrt::NewTrainingFramework::implementation
{
    struct GeneralModelShaderVS : GeneralModelShaderVST<GeneralModelShaderVS>
    {
        GeneralModelShaderVS() 
        {
            // Xaml objects should not call InitializeComponent during construction.
            // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
        }

        int32_t MyProperty();
        void MyProperty(int32_t value);

        void ClickHandler(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::RoutedEventArgs const& args);
    };
}

namespace winrt::NewTrainingFramework::factory_implementation
{
    struct GeneralModelShaderVS : GeneralModelShaderVST<GeneralModelShaderVS, implementation::GeneralModelShaderVS>
    {
    };
}
