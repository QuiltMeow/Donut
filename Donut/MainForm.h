#pragma once
#include "Donut.h"

namespace Donut {
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Threading;

	public ref class MainForm : public System::Windows::Forms::Form {
	public:
		MainForm() {
			InitializeComponent();
		}
	protected:
		~MainForm() {
			if (components) {
				delete components;
			}
		}
	private:
		System::Windows::Forms::TextBox^ txtRender;
		System::Windows::Forms::MenuStrip^ msMenu;
		System::Windows::Forms::ToolStripMenuItem^ tsmiCopy;
		System::Windows::Forms::ToolStripMenuItem^ tsmiExit;
		System::Windows::Forms::Label^ labelFocus;
		System::ComponentModel::IContainer^ components;

#pragma region Windows Form Designer generated code
		void InitializeComponent() {
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MainForm::typeid));
			this->txtRender = (gcnew System::Windows::Forms::TextBox());
			this->msMenu = (gcnew System::Windows::Forms::MenuStrip());
			this->tsmiCopy = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->tsmiExit = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->labelFocus = (gcnew System::Windows::Forms::Label());
			this->msMenu->SuspendLayout();
			this->SuspendLayout();
			//
			// txtRender
			//
			this->txtRender->BackColor = System::Drawing::Color::Black;
			this->txtRender->Dock = System::Windows::Forms::DockStyle::Fill;
			this->txtRender->Font = (gcnew System::Drawing::Font(L"細明體", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->txtRender->ForeColor = System::Drawing::Color::White;
			this->txtRender->Location = System::Drawing::Point(0, 24);
			this->txtRender->Multiline = true;
			this->txtRender->Name = L"txtRender";
			this->txtRender->Size = System::Drawing::Size(649, 412);
			this->txtRender->TabIndex = 2;
			this->txtRender->Enter += gcnew System::EventHandler(this, &MainForm::txtRender_Enter);
			//
			// msMenu
			//
			this->msMenu->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) { this->tsmiCopy, this->tsmiExit });
			this->msMenu->Location = System::Drawing::Point(0, 0);
			this->msMenu->Name = L"msMenu";
			this->msMenu->Size = System::Drawing::Size(649, 24);
			this->msMenu->TabIndex = 0;
			this->msMenu->Text = L"選單";
			//
			// tsmiCopy
			//
			this->tsmiCopy->Name = L"tsmiCopy";
			this->tsmiCopy->Size = System::Drawing::Size(43, 20);
			this->tsmiCopy->Text = L"複製";
			this->tsmiCopy->Click += gcnew System::EventHandler(this, &MainForm::tsmiCopy_Click);
			//
			// tsmiExit
			//
			this->tsmiExit->Name = L"tsmiExit";
			this->tsmiExit->Size = System::Drawing::Size(43, 20);
			this->tsmiExit->Text = L"離開";
			this->tsmiExit->Click += gcnew System::EventHandler(this, &MainForm::tsmiExit_Click);
			//
			// labelFocus
			//
			this->labelFocus->AutoSize = true;
			this->labelFocus->BackColor = System::Drawing::Color::Transparent;
			this->labelFocus->Location = System::Drawing::Point(-15, -15);
			this->labelFocus->Name = L"labelFocus";
			this->labelFocus->Size = System::Drawing::Size(0, 12);
			this->labelFocus->TabIndex = 1;
			//
			// MainForm
			//
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(649, 436);
			this->Controls->Add(this->labelFocus);
			this->Controls->Add(this->txtRender);
			this->Controls->Add(this->msMenu);
			this->DoubleBuffered = true;
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->ImeMode = System::Windows::Forms::ImeMode::Off;
			this->MainMenuStrip = this->msMenu;
			this->MaximizeBox = false;
			this->Name = L"MainForm";
			this->Text = L"甜甜圈";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &MainForm::MainForm_FormClosing);
			this->Load += gcnew System::EventHandler(this, &MainForm::MainForm_Load);
			this->msMenu->ResumeLayout(false);
			this->msMenu->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();
		}
#pragma endregion

		delegate void RenderTextUpdate(String^);
		RenderTextUpdate^ renderTextUpdate = gcnew RenderTextUpdate(this, &MainForm::updateRenderText);

		void updateRenderText(String^ result) {
			if (txtRender->InvokeRequired) {
				Invoke(renderTextUpdate, gcnew array<Object^> {
					result
				});
			}
			else {
				txtRender->Text = result;
			}
		}

		void renderTask() {
			float A = 0;
			float B = 0;

			DonutRender donut;
			while (true) {
				String^ result = gcnew String(donut.renderDonut(A, B).c_str());
				updateRenderText(result);
				A += 0.04;
				B += 0.02;
				if (isinf(A) || isinf(B)) {
					A = B = 0;
				}
			}
		}

		void startTask() {
			Thread^ renderThread = gcnew Thread(gcnew ThreadStart(this, &MainForm::renderTask));
			renderThread->Start();
		}

		void exit() {
			Environment::Exit(Environment::ExitCode);
		}

		void resetFocus() {
			ActiveControl = labelFocus;
		}

		System::Void MainForm_FormClosing(System::Object^ sender, System::Windows::Forms::FormClosingEventArgs^ e) {
			exit();
		}

		System::Void MainForm_Load(System::Object^ sender, System::EventArgs^ e) {
			resetFocus();
			startTask();
		}

		System::Void tsmiCopy_Click(System::Object^ sender, System::EventArgs^ e) {
			String^ text = txtRender->Text;
			if (text != String::Empty) {
				Clipboard::SetText(text);
			}
		}

		System::Void tsmiExit_Click(System::Object^ sender, System::EventArgs^ e) {
			exit();
		}

		System::Void txtRender_Enter(System::Object^ sender, System::EventArgs^ e) {
			resetFocus();
		}
	};
}