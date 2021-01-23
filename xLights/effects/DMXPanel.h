#pragma once

/***************************************************************
 * This source files comes from the xLights project
 * https://www.xlights.org
 * https://github.com/smeighan/xLights
 * See the github commit history for a record of contributing
 * developers.
 * Copyright claimed based on commit dates recorded in Github
 * License: https://github.com/smeighan/xLights/blob/master/License.txt
 **************************************************************/

 //(*Headers(DMXPanel)
 #include <wx/panel.h>
 class wxBitmapButton;
 class wxButton;
 class wxFlexGridSizer;
 class wxNotebook;
 class wxNotebookEvent;
 class wxSlider;
 class wxStaticText;
 class wxTextCtrl;
 //*)

#include "../BulkEditControls.h"
#include "EffectPanelUtils.h"

class Model;

class DMXPanel: public wxPanel
{
	std::list<Model*> GetActiveModels();

	public:

		DMXPanel(wxWindow* parent);
		virtual ~DMXPanel();
		void ValidateWindow();

		//(*Declarations(DMXPanel)
		BulkEditSlider* Slider_DMX10;
		BulkEditSlider* Slider_DMX11;
		BulkEditSlider* Slider_DMX12;
		BulkEditSlider* Slider_DMX13;
		BulkEditSlider* Slider_DMX14;
		BulkEditSlider* Slider_DMX15;
		BulkEditSlider* Slider_DMX16;
		BulkEditSlider* Slider_DMX17;
		BulkEditSlider* Slider_DMX18;
		BulkEditSlider* Slider_DMX19;
		BulkEditSlider* Slider_DMX1;
		BulkEditSlider* Slider_DMX20;
		BulkEditSlider* Slider_DMX21;
		BulkEditSlider* Slider_DMX22;
		BulkEditSlider* Slider_DMX23;
		BulkEditSlider* Slider_DMX24;
		BulkEditSlider* Slider_DMX25;
		BulkEditSlider* Slider_DMX26;
		BulkEditSlider* Slider_DMX27;
		BulkEditSlider* Slider_DMX28;
		BulkEditSlider* Slider_DMX29;
		BulkEditSlider* Slider_DMX2;
		BulkEditSlider* Slider_DMX30;
		BulkEditSlider* Slider_DMX31;
		BulkEditSlider* Slider_DMX32;
		BulkEditSlider* Slider_DMX33;
		BulkEditSlider* Slider_DMX34;
		BulkEditSlider* Slider_DMX35;
		BulkEditSlider* Slider_DMX36;
		BulkEditSlider* Slider_DMX37;
		BulkEditSlider* Slider_DMX38;
		BulkEditSlider* Slider_DMX39;
		BulkEditSlider* Slider_DMX3;
		BulkEditSlider* Slider_DMX40;
		BulkEditSlider* Slider_DMX4;
		BulkEditSlider* Slider_DMX5;
		BulkEditSlider* Slider_DMX6;
		BulkEditSlider* Slider_DMX7;
		BulkEditSlider* Slider_DMX8;
		BulkEditSlider* Slider_DMX9;
		BulkEditValueCurveButton* ValueCurve_DMX10;
		BulkEditValueCurveButton* ValueCurve_DMX11;
		BulkEditValueCurveButton* ValueCurve_DMX12;
		BulkEditValueCurveButton* ValueCurve_DMX13;
		BulkEditValueCurveButton* ValueCurve_DMX14;
		BulkEditValueCurveButton* ValueCurve_DMX15;
		BulkEditValueCurveButton* ValueCurve_DMX16;
		BulkEditValueCurveButton* ValueCurve_DMX17;
		BulkEditValueCurveButton* ValueCurve_DMX18;
		BulkEditValueCurveButton* ValueCurve_DMX19;
		BulkEditValueCurveButton* ValueCurve_DMX1;
		BulkEditValueCurveButton* ValueCurve_DMX20;
		BulkEditValueCurveButton* ValueCurve_DMX21;
		BulkEditValueCurveButton* ValueCurve_DMX22;
		BulkEditValueCurveButton* ValueCurve_DMX23;
		BulkEditValueCurveButton* ValueCurve_DMX24;
		BulkEditValueCurveButton* ValueCurve_DMX25;
		BulkEditValueCurveButton* ValueCurve_DMX26;
		BulkEditValueCurveButton* ValueCurve_DMX27;
		BulkEditValueCurveButton* ValueCurve_DMX28;
		BulkEditValueCurveButton* ValueCurve_DMX29;
		BulkEditValueCurveButton* ValueCurve_DMX2;
		BulkEditValueCurveButton* ValueCurve_DMX30;
		BulkEditValueCurveButton* ValueCurve_DMX31;
		BulkEditValueCurveButton* ValueCurve_DMX32;
		BulkEditValueCurveButton* ValueCurve_DMX33;
		BulkEditValueCurveButton* ValueCurve_DMX34;
		BulkEditValueCurveButton* ValueCurve_DMX35;
		BulkEditValueCurveButton* ValueCurve_DMX36;
		BulkEditValueCurveButton* ValueCurve_DMX37;
		BulkEditValueCurveButton* ValueCurve_DMX38;
		BulkEditValueCurveButton* ValueCurve_DMX39;
		BulkEditValueCurveButton* ValueCurve_DMX3;
		BulkEditValueCurveButton* ValueCurve_DMX40;
		BulkEditValueCurveButton* ValueCurve_DMX4;
		BulkEditValueCurveButton* ValueCurve_DMX5;
		BulkEditValueCurveButton* ValueCurve_DMX6;
		BulkEditValueCurveButton* ValueCurve_DMX7;
		BulkEditValueCurveButton* ValueCurve_DMX8;
		BulkEditValueCurveButton* ValueCurve_DMX9;
		wxButton* ButtonRemap;
		wxButton* Button_SaveAsState;
		wxFlexGridSizer* FlexGridSizer1;
		wxFlexGridSizer* FlexGridSizer2;
		wxFlexGridSizer* FlexGridSizer_Main;
		wxFlexGridSizer* FlexGridSizer_Panel1;
		wxFlexGridSizer* FlexGridSizer_Panel2;
		wxNotebook* Notebook7;
		wxPanel* ChannelPanel1;
		wxPanel* ChannelPanel2;
		wxPanel* ChannelPanel3;
		wxPanel* ChannelPanel4;
		wxStaticText* Label_DMX10;
		wxStaticText* Label_DMX11;
		wxStaticText* Label_DMX12;
		wxStaticText* Label_DMX13;
		wxStaticText* Label_DMX14;
		wxStaticText* Label_DMX15;
		wxStaticText* Label_DMX16;
		wxStaticText* Label_DMX17;
		wxStaticText* Label_DMX18;
		wxStaticText* Label_DMX19;
		wxStaticText* Label_DMX1;
		wxStaticText* Label_DMX20;
		wxStaticText* Label_DMX21;
		wxStaticText* Label_DMX22;
		wxStaticText* Label_DMX23;
		wxStaticText* Label_DMX24;
		wxStaticText* Label_DMX25;
		wxStaticText* Label_DMX26;
		wxStaticText* Label_DMX27;
		wxStaticText* Label_DMX28;
		wxStaticText* Label_DMX29;
		wxStaticText* Label_DMX2;
		wxStaticText* Label_DMX30;
		wxStaticText* Label_DMX31;
		wxStaticText* Label_DMX32;
		wxStaticText* Label_DMX33;
		wxStaticText* Label_DMX34;
		wxStaticText* Label_DMX35;
		wxStaticText* Label_DMX36;
		wxStaticText* Label_DMX37;
		wxStaticText* Label_DMX38;
		wxStaticText* Label_DMX39;
		wxStaticText* Label_DMX3;
		wxStaticText* Label_DMX40;
		wxStaticText* Label_DMX4;
		wxStaticText* Label_DMX5;
		wxStaticText* Label_DMX6;
		wxStaticText* Label_DMX7;
		wxStaticText* Label_DMX8;
		wxStaticText* Label_DMX9;
		//*)

	protected:

		//(*Identifiers(DMXPanel)
		static const long ID_STATICTEXT_DMX1;
		static const long ID_SLIDER_DMX1;
		static const long ID_VALUECURVE_DMX1;
		static const long IDD_TEXTCTRL_DMX1;
		static const long ID_STATICTEXT_DMX2;
		static const long ID_SLIDER_DMX2;
		static const long ID_VALUECURVE_DMX2;
		static const long IDD_TEXTCTRL_DMX2;
		static const long ID_STATICTEXT_DMX3;
		static const long ID_SLIDER_DMX3;
		static const long ID_VALUECURVE_DMX3;
		static const long IDD_TEXTCTRL_DMX3;
		static const long ID_STATICTEXT_DMX4;
		static const long ID_SLIDER_DMX4;
		static const long ID_VALUECURVE_DMX4;
		static const long IDD_TEXTCTRL_DMX4;
		static const long ID_STATICTEXT_DMX5;
		static const long ID_SLIDER_DMX5;
		static const long ID_VALUECURVE_DMX5;
		static const long IDD_TEXTCTRL_DMX5;
		static const long ID_STATICTEXT_DMX6;
		static const long ID_SLIDER_DMX6;
		static const long ID_VALUECURVE_DMX6;
		static const long IDD_TEXTCTRL_DMX6;
		static const long ID_STATICTEXT_DMX7;
		static const long ID_SLIDER_DMX7;
		static const long ID_VALUECURVE_DMX7;
		static const long IDD_TEXTCTRL_DMX7;
		static const long ID_STATICTEXT_DMX8;
		static const long ID_SLIDER_DMX8;
		static const long ID_VALUECURVE_DMX8;
		static const long IDD_TEXTCTRL_DMX8;
		static const long ID_STATICTEXT_DMX9;
		static const long ID_SLIDER_DMX9;
		static const long ID_VALUECURVE_DMX9;
		static const long IDD_TEXTCTRL_DMX9;
		static const long ID_STATICTEXT_DMX10;
		static const long ID_SLIDER_DMX10;
		static const long ID_VALUECURVE_DMX10;
		static const long IDD_TEXTCTRL_DMX10;
		static const long ID_PANEL6;
		static const long ID_STATICTEXT_DMX11;
		static const long ID_SLIDER_DMX11;
		static const long ID_VALUECURVE_DMX11;
		static const long IDD_TEXTCTRL_DMX11;
		static const long ID_STATICTEXT_DMX12;
		static const long ID_SLIDER_DMX12;
		static const long ID_VALUECURVE_DMX12;
		static const long IDD_TEXTCTRL_DMX12;
		static const long ID_STATICTEXT_DMX13;
		static const long ID_SLIDER_DMX13;
		static const long ID_VALUECURVE_DMX13;
		static const long IDD_TEXTCTRL_DMX13;
		static const long ID_STATICTEXT_DMX14;
		static const long ID_SLIDER_DMX14;
		static const long ID_VALUECURVE_DMX14;
		static const long IDD_TEXTCTRL_DMX14;
		static const long ID_STATICTEXT_DMX15;
		static const long ID_SLIDER_DMX15;
		static const long ID_VALUECURVE_DMX15;
		static const long IDD_TEXTCTRL_DMX15;
		static const long ID_STATICTEXT_DMX16;
		static const long ID_SLIDER_DMX16;
		static const long ID_VALUECURVE_DMX16;
		static const long IDD_TEXTCTRL_DMX16;
		static const long ID_STATICTEXT_DMX17;
		static const long ID_SLIDER_DMX17;
		static const long ID_VALUECURVE_DMX17;
		static const long IDD_TEXTCTRL_DMX17;
		static const long ID_STATICTEXT_DMX18;
		static const long ID_SLIDER_DMX18;
		static const long ID_VALUECURVE_DMX18;
		static const long IDD_TEXTCTRL_DMX18;
		static const long ID_STATICTEXT_DMX19;
		static const long ID_SLIDER_DMX19;
		static const long ID_VALUECURVE_DMX19;
		static const long IDD_TEXTCTRL_DMX19;
		static const long ID_STATICTEXT_DMX20;
		static const long ID_SLIDER_DMX20;
		static const long ID_VALUECURVE_DMX20;
		static const long IDD_TEXTCTRL_DMX20;
		static const long ID_PANEL28;
		static const long ID_STATICTEXT_DMX21;
		static const long ID_SLIDER_DMX21;
		static const long ID_VALUECURVE_DMX21;
		static const long IDD_TEXTCTRL_DMX21;
		static const long ID_STATICTEXT_DMX22;
		static const long ID_SLIDER_DMX22;
		static const long ID_VALUECURVE_DMX22;
		static const long IDD_TEXTCTRL_DMX22;
		static const long ID_STATICTEXT_DMX23;
		static const long ID_SLIDER_DMX23;
		static const long ID_VALUECURVE_DMX23;
		static const long IDD_TEXTCTRL_DMX23;
		static const long ID_STATICTEXT_DMX24;
		static const long ID_SLIDER_DMX24;
		static const long ID_VALUECURVE_DMX24;
		static const long IDD_TEXTCTRL_DMX24;
		static const long ID_STATICTEXT_DMX25;
		static const long ID_SLIDER_DMX25;
		static const long ID_VALUECURVE_DMX25;
		static const long IDD_TEXTCTRL_DMX25;
		static const long ID_STATICTEXT_DMX26;
		static const long ID_SLIDER_DMX26;
		static const long ID_VALUECURVE_DMX26;
		static const long IDD_TEXTCTRL_DMX26;
		static const long ID_STATICTEXT_DMX27;
		static const long ID_SLIDER_DMX27;
		static const long ID_VALUECURVE_DMX27;
		static const long IDD_TEXTCTRL_DMX27;
		static const long ID_STATICTEXT_DMX28;
		static const long ID_SLIDER_DMX28;
		static const long ID_VALUECURVE_DMX28;
		static const long IDD_TEXTCTRL_DMX28;
		static const long ID_STATICTEXT_DMX29;
		static const long ID_SLIDER_DMX29;
		static const long ID_VALUECURVE_DMX29;
		static const long IDD_TEXTCTRL_DMX29;
		static const long ID_STATICTEXT_DMX30;
		static const long ID_SLIDER_DMX30;
		static const long ID_VALUECURVE_DMX30;
		static const long IDD_TEXTCTRL_DMX30;
		static const long ID_PANEL1;
		static const long ID_STATICTEXT_DMX31;
		static const long ID_SLIDER_DMX31;
		static const long ID_VALUECURVE_DMX31;
		static const long IDD_TEXTCTRL_DMX31;
		static const long ID_STATICTEXT_DMX32;
		static const long ID_SLIDER_DMX32;
		static const long ID_VALUECURVE_DMX32;
		static const long IDD_TEXTCTRL_DMX32;
		static const long ID_STATICTEXT_DMX33;
		static const long ID_SLIDER_DMX33;
		static const long ID_VALUECURVE_DMX33;
		static const long IDD_TEXTCTRL_DMX33;
		static const long ID_STATICTEXT_DMX34;
		static const long ID_SLIDER_DMX34;
		static const long ID_VALUECURVE_DMX34;
		static const long IDD_TEXTCTRL_DMX34;
		static const long ID_STATICTEXT_DMX35;
		static const long ID_SLIDER_DMX35;
		static const long ID_VALUECURVE_DMX35;
		static const long IDD_TEXTCTRL_DMX35;
		static const long ID_STATICTEXT_DMX36;
		static const long ID_SLIDER_DMX36;
		static const long ID_VALUECURVE_DMX36;
		static const long IDD_TEXTCTRL_DMX36;
		static const long ID_STATICTEXT_DMX37;
		static const long ID_SLIDER_DMX37;
		static const long ID_VALUECURVE_DMX37;
		static const long IDD_TEXTCTRL_DMX37;
		static const long ID_STATICTEXT_DMX38;
		static const long ID_SLIDER_DMX38;
		static const long ID_VALUECURVE_DMX38;
		static const long IDD_TEXTCTRL_DMX38;
		static const long ID_STATICTEXT_DMX39;
		static const long ID_SLIDER_DMX39;
		static const long ID_VALUECURVE_DMX39;
		static const long IDD_TEXTCTRL_DMX39;
		static const long ID_STATICTEXT_DMX40;
		static const long ID_SLIDER_DMX40;
		static const long ID_VALUECURVE_DMX40;
		static const long IDD_TEXTCTRL_DMX40;
		static const long ID_PANEL3;
		static const long ID_NOTEBOOK1;
		static const long ID_BUTTON1;
		static const long ID_BUTTON2;
		//*)

	public:

		DECLARE_PANEL_EVENT_HANDLERS()

		//(*Handlers(DMXPanel)
		void OnButtonRemapClick(wxCommandEvent& event);
		void OnButton_SaveAsStateClick(wxCommandEvent& event);
		//*)

        void OnButtonRemapRClick(wxCommandEvent& event);
        void OnChoicePopup(wxCommandEvent& event);

    DECLARE_EVENT_TABLE()
};
