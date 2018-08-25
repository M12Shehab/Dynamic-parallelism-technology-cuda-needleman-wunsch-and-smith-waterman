#pragma once
#include <stdlib.h>
//#include <string.h>
#include <time.h>
#include <windows.h>
#include <vector>
#include <omp.h>
#include <string>
//#include <thread>



#define MAX(x,y) ((x) > (y) ? (x) : (y))
extern void Kernal_Test(int *a, int *b, int* c, int &count);

//------- Needleman Wunschal gorithm-----------
extern void NW_CPU(char *Adata, char *Bdata, int alen, int blen,  int *NewH, clock_t &Begain, clock_t &End);
extern void NW_GPU(char *Adata, char *Bdata, int alen, int blen, int *NewH, clock_t &Begain, clock_t &End, clock_t &CreateBegain, clock_t &CreateEnd);
//---------------------------------------------
//------- Smith–Waterman algorithm ------------
extern void SM_CPU(char *Adata, char *Bdata, int alen, int blen, int *NewH, clock_t &Begain, clock_t &End);
extern void SM_GPU(char *Adata, char *Bdata, int alen, int blen, int *NewH, clock_t &Begain, clock_t &End, clock_t &CreateBegain, clock_t &CreateEnd);
omp_lock_t my_lock;
using namespace std;


//using namespace Concurrency;
namespace GeneSearchEngin {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;
	using namespace System::Collections;
	using namespace System::Threading;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  btnOpen;
	private: System::Windows::Forms::TextBox^  txtDisplay;
	private: System::Windows::Forms::Button^  btnRun;
	private: System::Windows::Forms::Label^  lblCPU;
	private: System::Windows::Forms::Label^  lblGPU;
	private: System::Windows::Forms::RichTextBox^  richTextBox1;
	private: System::Windows::Forms::FolderBrowserDialog^  folderBrowserDialog1;
	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::RadioButton^  rdbGPU;
	private: System::Windows::Forms::RadioButton^  rdbCPU;
	private: System::Windows::Forms::CheckBox^  chkDynamic;
	private: System::Windows::Forms::ListBox^  listBox1;
	private: System::Windows::Forms::GroupBox^  groupBox2;
	private: System::Windows::Forms::RadioButton^  rdbNW;


	private: System::Windows::Forms::RadioButton^  rdbSM;


	private: System::Windows::Forms::ListBox^  listBox2;

	protected:

	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->btnOpen = (gcnew System::Windows::Forms::Button());
			this->txtDisplay = (gcnew System::Windows::Forms::TextBox());
			this->btnRun = (gcnew System::Windows::Forms::Button());
			this->lblCPU = (gcnew System::Windows::Forms::Label());
			this->lblGPU = (gcnew System::Windows::Forms::Label());
			this->richTextBox1 = (gcnew System::Windows::Forms::RichTextBox());
			this->folderBrowserDialog1 = (gcnew System::Windows::Forms::FolderBrowserDialog());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->chkDynamic = (gcnew System::Windows::Forms::CheckBox());
			this->rdbGPU = (gcnew System::Windows::Forms::RadioButton());
			this->rdbCPU = (gcnew System::Windows::Forms::RadioButton());
			this->listBox1 = (gcnew System::Windows::Forms::ListBox());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->rdbNW = (gcnew System::Windows::Forms::RadioButton());
			this->rdbSM = (gcnew System::Windows::Forms::RadioButton());
			this->listBox2 = (gcnew System::Windows::Forms::ListBox());
			this->groupBox1->SuspendLayout();
			this->groupBox2->SuspendLayout();
			this->SuspendLayout();
			// 
			// btnOpen
			// 
			this->btnOpen->Location = System::Drawing::Point(278, 10);
			this->btnOpen->Name = L"btnOpen";
			this->btnOpen->Size = System::Drawing::Size(75, 23);
			this->btnOpen->TabIndex = 0;
			this->btnOpen->Text = L"Open";
			this->btnOpen->UseVisualStyleBackColor = true;
			this->btnOpen->Click += gcnew System::EventHandler(this, &MyForm::btnOpen_Click);
			// 
			// txtDisplay
			// 
			this->txtDisplay->Location = System::Drawing::Point(12, 12);
			this->txtDisplay->Name = L"txtDisplay";
			this->txtDisplay->Size = System::Drawing::Size(260, 20);
			this->txtDisplay->TabIndex = 1;
			// 
			// btnRun
			// 
			this->btnRun->Location = System::Drawing::Point(12, 158);
			this->btnRun->Name = L"btnRun";
			this->btnRun->Size = System::Drawing::Size(75, 23);
			this->btnRun->TabIndex = 2;
			this->btnRun->Text = L"Run";
			this->btnRun->UseVisualStyleBackColor = true;
			this->btnRun->Click += gcnew System::EventHandler(this, &MyForm::btnRun_Click);
			// 
			// lblCPU
			// 
			this->lblCPU->AutoSize = true;
			this->lblCPU->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblCPU->Location = System::Drawing::Point(12, 116);
			this->lblCPU->Name = L"lblCPU";
			this->lblCPU->Size = System::Drawing::Size(118, 20);
			this->lblCPU->TabIndex = 3;
			this->lblCPU->Text = L"CPU Time = 0";
			// 
			// lblGPU
			// 
			this->lblGPU->AutoSize = true;
			this->lblGPU->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblGPU->Location = System::Drawing::Point(12, 95);
			this->lblGPU->Name = L"lblGPU";
			this->lblGPU->Size = System::Drawing::Size(120, 20);
			this->lblGPU->TabIndex = 4;
			this->lblGPU->Text = L"GPU Time = 0";
			// 
			// richTextBox1
			// 
			this->richTextBox1->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->richTextBox1->Location = System::Drawing::Point(0, 187);
			this->richTextBox1->Name = L"richTextBox1";
			this->richTextBox1->Size = System::Drawing::Size(1144, 259);
			this->richTextBox1->TabIndex = 5;
			this->richTextBox1->Text = L"";
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->chkDynamic);
			this->groupBox1->Controls->Add(this->rdbGPU);
			this->groupBox1->Controls->Add(this->rdbCPU);
			this->groupBox1->Location = System::Drawing::Point(359, 10);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(176, 88);
			this->groupBox1->TabIndex = 6;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Device";
			// 
			// chkDynamic
			// 
			this->chkDynamic->AutoSize = true;
			this->chkDynamic->Location = System::Drawing::Point(70, 54);
			this->chkDynamic->Name = L"chkDynamic";
			this->chkDynamic->Size = System::Drawing::Size(104, 17);
			this->chkDynamic->TabIndex = 2;
			this->chkDynamic->Text = L"Dynamic Parallel";
			this->chkDynamic->UseVisualStyleBackColor = true;
			// 
			// rdbGPU
			// 
			this->rdbGPU->AutoSize = true;
			this->rdbGPU->Location = System::Drawing::Point(16, 53);
			this->rdbGPU->Name = L"rdbGPU";
			this->rdbGPU->Size = System::Drawing::Size(48, 17);
			this->rdbGPU->TabIndex = 1;
			this->rdbGPU->Text = L"GPU";
			this->rdbGPU->UseVisualStyleBackColor = true;
			// 
			// rdbCPU
			// 
			this->rdbCPU->AutoSize = true;
			this->rdbCPU->Checked = true;
			this->rdbCPU->Location = System::Drawing::Point(16, 30);
			this->rdbCPU->Name = L"rdbCPU";
			this->rdbCPU->Size = System::Drawing::Size(47, 17);
			this->rdbCPU->TabIndex = 0;
			this->rdbCPU->TabStop = true;
			this->rdbCPU->Text = L"CPU";
			this->rdbCPU->UseVisualStyleBackColor = true;
			// 
			// listBox1
			// 
			this->listBox1->FormattingEnabled = true;
			this->listBox1->HorizontalScrollbar = true;
			this->listBox1->Location = System::Drawing::Point(721, 14);
			this->listBox1->Name = L"listBox1";
			this->listBox1->Size = System::Drawing::Size(245, 160);
			this->listBox1->TabIndex = 7;
			// 
			// groupBox2
			// 
			this->groupBox2->Controls->Add(this->rdbNW);
			this->groupBox2->Controls->Add(this->rdbSM);
			this->groupBox2->Location = System::Drawing::Point(539, 12);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(176, 88);
			this->groupBox2->TabIndex = 8;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"Device";
			// 
			// rdbNW
			// 
			this->rdbNW->AutoSize = true;
			this->rdbNW->Location = System::Drawing::Point(16, 53);
			this->rdbNW->Name = L"rdbNW";
			this->rdbNW->Size = System::Drawing::Size(122, 17);
			this->rdbNW->TabIndex = 1;
			this->rdbNW->Text = L"Needleman-Wunsch";
			this->rdbNW->UseVisualStyleBackColor = true;
			// 
			// rdbSM
			// 
			this->rdbSM->AutoSize = true;
			this->rdbSM->Checked = true;
			this->rdbSM->Location = System::Drawing::Point(16, 30);
			this->rdbSM->Name = L"rdbSM";
			this->rdbSM->Size = System::Drawing::Size(105, 17);
			this->rdbSM->TabIndex = 0;
			this->rdbSM->TabStop = true;
			this->rdbSM->Text = L"Smith–Waterman";
			this->rdbSM->UseVisualStyleBackColor = true;
			// 
			// listBox2
			// 
			this->listBox2->FormattingEnabled = true;
			this->listBox2->HorizontalScrollbar = true;
			this->listBox2->Location = System::Drawing::Point(972, 12);
			this->listBox2->Name = L"listBox2";
			this->listBox2->Size = System::Drawing::Size(152, 160);
			this->listBox2->TabIndex = 9;
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1144, 446);
			this->Controls->Add(this->listBox2);
			this->Controls->Add(this->groupBox2);
			this->Controls->Add(this->listBox1);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->richTextBox1);
			this->Controls->Add(this->lblGPU);
			this->Controls->Add(this->lblCPU);
			this->Controls->Add(this->btnRun);
			this->Controls->Add(this->txtDisplay);
			this->Controls->Add(this->btnOpen);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->groupBox2->ResumeLayout(false);
			this->groupBox2->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
		array<String^>^fileEntries;
		long double *GPUTimes;
		long double *Addtionals;
		long double *Total;
		long double *FileTimes;

	private: System::Void btnOpen_Click(System::Object^  sender, System::EventArgs^  e) {
		// Display the openFile Dialog.
		System::Windows::Forms::DialogResult result = folderBrowserDialog1->ShowDialog();
		String^ *files;
		// OK button was pressed.
		if (result == System::Windows::Forms::DialogResult::OK)
		{
			txtDisplay->Text = folderBrowserDialog1->SelectedPath;
			fileEntries = Directory::GetFiles(txtDisplay->Text);
			IEnumerator^ files = fileEntries->GetEnumerator();
			while (files->MoveNext())
			{
				String^ fileName = safe_cast<String^>(files->Current);
				listBox1->Items->Add(fileName);
			}
		}
	}

	private: System::Void btnRun_Click(System::Object^  sender, System::EventArgs^  e) {
		IEnumerator^ files = fileEntries->GetEnumerator();
		int count = 0;
		String^ pattern = "";
		long double Total_CPU = 0;
		long double Total_GPU = 0;
		bool Append = false;

		while (files->MoveNext())
		{
			String^ fileName = safe_cast<String^>(files->Current);
			clock_t s, e;
			
			if (count == 0)
			{
				pattern = ProcessFile(fileName);
				GPUTimes = new long double[listBox1->Items->Count];
				Addtionals = new long double[listBox1->Items->Count];
				FileTimes = new long double[listBox1->Items->Count];
				Total = new long double[listBox1->Items->Count];
				/*count++;*/
			}
			else
			{
				if (rdbSM->Checked)
				{
					if (count > 1)
					{
						Append = true;
					}
					s = clock();
					String^ str = ProcessFile(fileName);
					e = clock();
					long double Addition = (double)(e + s) / CLOCKS_PER_SEC;
					if (rdbCPU->Checked)
					{
						if (rdbSM->Checked)
						Total_CPU += Run_SW_CPU(Addition, pattern, str, Append);
						else
							Total_CPU += Run_NW_CPU(Addition, pattern, str, Append);
					}
					else if (rdbGPU->Checked)
					{
						if (!chkDynamic->Checked)
						{
							Total_GPU += Run_SW_GPU(Addition, pattern, str, Append, count);
						}
						else
						{
							Run_Dynamic(pattern);
							break;
						}

					}
				}

				if (rdbNW->Checked)
				{
					if (count > 1)
					{
						Append = true;
					}
					s = clock();
					String^ str = ProcessFile(fileName);
					e = clock();
					long double Addition = (double)(e + s) / CLOCKS_PER_SEC;
					if (rdbCPU->Checked)
					{
						Total_CPU += Run_NW_CPU(Addition, pattern, str, Append);
					}
					else if (rdbGPU->Checked)
					{
						if (!chkDynamic->Checked)
						{
							Total_GPU += Run_NW_GPU(Addition, pattern, str, Append, count);
						}
						else
						{
							Run_Dynamic_NW(pattern);
							break;
						}

					}
				}
			}
			count++;
		}

		lblCPU->Text = "Total CPU = " + Total_CPU;
		StreamWriter^ wr = gcnew  StreamWriter("SM_CPU.txt", true);
		wr->Write(lblCPU->Text);
		wr->Close();

		if (rdbSM->Checked && rdbGPU->Checked)
		{
			if (!chkDynamic->Checked)
			{
				lblGPU->Text = "Total GPU = " + Total_GPU;

				StreamWriter^ wr = gcnew  StreamWriter("SM_GPU.txt", false);
				wr->Write("#Qurey Time, Memory allocation , I/O Time , Total\r\n");
				wr->Close();

				StreamWriter^ wr1 = gcnew  StreamWriter("SM_GPU.txt", true);
				String^ temp = "";
				for (int x = 0; x < listBox1->Items->Count; x++)
				{
					if (GPUTimes[x] < 0)
					{
						GPUTimes[x] = 0;
					}

					if (Addtionals[x] < 0)
					{
						Addtionals[x] = 0;
					}

					if (FileTimes[x] < 0)
					{
						FileTimes[x] = 0;
					}

					if (Total[x] < 0)
					{
						Total[x] = 0;
					}
					temp += GPUTimes[x] + " , " + Addtionals[x] + " , " + FileTimes[x] + " , " + Total[x] + "\r\n";
				}

				wr1->Write(temp + lblGPU->Text);
				wr1->Close();
			}
		}

		if (rdbNW->Checked && rdbGPU->Checked)
		{
			if (!chkDynamic->Checked)
			{
				lblGPU->Text = "Total GPU = " + Total_GPU;

				StreamWriter^ wr = gcnew  StreamWriter("NW_GPU.txt", false);
				wr->Write("#Qurey Time, Memory allocation , I/O Time , Total\r\n");
				wr->Close();

				StreamWriter^ wr1 = gcnew  StreamWriter("NW_GPU.txt", true);
				String^ temp = "";
				for (int x = 0; x < listBox1->Items->Count; x++)
				{
					if (GPUTimes[x] < 0)
					{
						GPUTimes[x] = 0;
					}

					if (Addtionals[x] < 0)
					{
						Addtionals[x] = 0;
					}

					if (FileTimes[x] < 0)
					{
						FileTimes[x] = 0;
					}

					if (Total[x] < 0)
					{
						Total[x] = 0;
					}
					temp += GPUTimes[x] + " , " + Addtionals[x] + " , " + FileTimes[x] + " , " + Total[x] + "\r\n";
				}

				wr1->Write(temp + lblGPU->Text);
				wr1->Close();
			}
		}


		//Run_NW();
		//Run_SW();
	}
			
			 void Run_Dynamic(String^ pattern)
			 {

				 clock_t s, e;
				 long double Total_GPU = 0;
				 // unsigned int n = thread::hardware_concurrency();
				 s = clock();
				 for (int i = 1; i < listBox1->Items->Count; i++)
				 {
					 String^ d = ProcessFile(listBox1->Items[i]->ToString());
					 listBox2->Items->Add(ProcessFile(listBox1->Items[i]->ToString()));
				 }
				 e = clock();
				 long double Addition = (double)(e + s) / CLOCKS_PER_SEC;
				 lblGPU->Text = "Total GPU = " + Addition;

				 int iCPU = 2;
				 int workers = listBox2->Items->Count / iCPU;
				 omp_set_num_threads(iCPU);
				 int i = 0;
				 GPUTimes = new long double[listBox2->Items->Count];
				 Addtionals = new long double[listBox2->Items->Count];
				 FileTimes = new long double[listBox2->Items->Count];
				 Total = new long double[listBox2->Items->Count];

				 for (int j = 0; j < workers; j += 2)
				 {
#pragma omp parallel
					 {

						 i = omp_get_thread_num() + j;

						 Total_GPU += Run_SW_GPU(0, pattern, listBox2->Items[i]->ToString(), true, i);

					 }
					 Sleep(10);
				 }

				 for (int y = i; y < listBox2->Items->Count; y++)
				 {
					 Total_GPU += Run_SW_GPU(0, pattern, listBox2->Items[y]->ToString(), true, y);
				 }
				 omp_destroy_lock(&my_lock);

				 lblGPU->Text = "Total GPU = " + (Total_GPU + Addition);
				 StreamWriter^ wr = gcnew  StreamWriter("SM_GPU.txt", false);
				 wr->Write("#Qurey Time, Memory allocation , I/O Time , Total\r\n");
				 wr->Close();

				 StreamWriter^ wr1 = gcnew  StreamWriter("SM_GPU.txt", true);
				 String^ temp = "";
				 for (int x = 0; x < listBox2->Items->Count; x++)
				 {
					 if (GPUTimes[x] < 0)
					 {
						 GPUTimes[x] = 0;
					 }

					 if (Addtionals[x] < 0)
					 {
						 Addtionals[x] = 0;
					 }

					 if (FileTimes[x] < 0)
					 {
						 FileTimes[x] = 0;
					 }

					 if (Total[x] < 0)
					 {
						 Total[x] = 0;
					 }
					 temp += GPUTimes[x] + " , " + Addtionals[x] + " , " + FileTimes[x] + " , " + Total[x] + "\r\n";
				 }

				 wr1->Write(temp + lblGPU->Text);
				 wr1->Close();

			 }

			 String^ ProcessFile(String^ path)
			 {
				 try
				 {
					 StreamReader^ din = File::OpenText(path);
					 String^ str;
					 String^ temp;
					 int count = 0;
					 while ((str = din->ReadLine()) != nullptr)
					 {
						 count++;
						 temp = str;
						// Console::WriteLine("line {0}: {1}", count, str);
					 }
					 return temp;
				 }
				 catch (Exception^ e)
				 {
					 return "";
				 }
			 }
			 long double Run_SW_CPU(long double FileTime, String^ ptr1, String^ ptr2,bool file_flag)
			 {
				
				 StreamWriter^ wr = gcnew  StreamWriter("SM_CPU.txt", file_flag);
				 if (!file_flag)
				 {
					 wr->Write("#Qurey Time, Memory allocation , I/O Time , Total\r\n");
				 }
				
				 //-----------------------------------------------------
				 clock_t FunctionCPUStart, FunctionCPUStop, CPUStart, CPUEnd;

				 clock_t CStart, CEnd, AStart, AEnd;
				 //-----------------------------------------------------

				 long int LENGHT = MAX(ptr1->Length, ptr2->Length);
				 char *a;
				 char *b;
				 long int t;
				 int *NewH, *NewHGPU;

				 CStart = clock();
				 a = new char[LENGHT];
				 b = new char[LENGHT];
				 CEnd = clock();

				 for (t = 0; t < LENGHT - 1; ++t)
				 {
					 char c1,c2;
					 if (t < ptr1->Length)
					 {
						 c1 =  ptr1[t];
					 }
					 else
					 {
						 c1 = '-';
					 }

					 if (t < ptr2->Length)
					 {
						 c2 = ptr2[t];
					 }
					 else
					 {
						 c2 = '-';
					 }
					 a[t] = c1;
					 b[t] = c2;
				 }
				 a[t] = '\0';
				 b[t] = '\0';
				 int alen = strlen(a) + 1;
				 int blen = strlen(b) + 1;
				 AStart = clock();
				 NewH = new int[alen * blen];
				 AEnd = clock();

				 long double Addition = (double)((AEnd + CEnd) - (CStart + AStart)) / CLOCKS_PER_SEC;
				 //----CPU-----
				 // void SM_CPU(char *Adata, char *Bdata, int alen, int blen, int *NewH, clock_t &Begain, clock_t &End);
				 FunctionCPUStart = clock();
				 SM_CPU(a, b, alen, blen,NewH, CPUStart, CPUEnd);
				 FunctionCPUStop = clock();
				 long double CPUTime1 = (double)(FunctionCPUStop - FunctionCPUStart) / CLOCKS_PER_SEC;
				 long double CPUTime2 = (double)(CPUEnd - CPUStart) / CLOCKS_PER_SEC;
				 //lblCPU->Text = "CPU Time of function = " + (CPUTime1 + Addition + FileTime) + " , CPU = " + (CPUTime2 + Addition);
				 //txtDisplay->Text = "H CPU = " + NewH[alen - 1];
				 //------------
				 String^ txt = CPUTime2 + " , " + Addition + " , " + FileTime+" , "+ (CPUTime1 + Addition + FileTime).ToString()+"\r\n";
				 wr->Write(txt);
				 wr->Close();
				 richTextBox1->Text += "str1 = "+ptr1+"\r\nstr2 = "+ptr2+"\r\nCPU Time : "+CPUTime2+"\r\n------------\r\n";
				 return((CPUTime1 + Addition + FileTime));
			 }

			 long double Run_SW_GPU(long double FileTime, String^ ptr1, String^ ptr2, bool file_flag,int x)
			 {

				 
				 //-----------------------------------------------------
				// clock_t FunctionCPUStart, FunctionCPUStop, CPUStart, CPUEnd;
				 clock_t FunctionGPUStart, FunctionGPUStop, GPUStart, GPUEnd;

				 clock_t CStart, CEnd, AStart, AEnd;
				 //-----------------------------------------------------

				 long int LENGHT = MAX(ptr1->Length, ptr2->Length);
				 char *a;
				 char *b;
				 long int t;
				 int *NewH, *NewHGPU;

				 //CStart = clock();
				 a = new char[LENGHT];
				 b = new char[LENGHT];
				// CEnd = clock();

				 for (t = 0; t < LENGHT - 1; ++t)
				 {
					 char c1, c2;
					 if (t < ptr1->Length)
					 {
						 c1 = ptr1[t];
					 }
					 else
					 {
						 c1 = '-';
					 }

					 if (t < ptr2->Length)
					 {
						 c2 = ptr2[t];
					 }
					 else
					 {
						 c2 = '-';
					 }
					 a[t] = c1;
					 b[t] = c2;
					 //printf("Random number: %d, char = %c\n",num,c);
				 }
				 a[t] = '\0';
				 b[t] = '\0';
				 int alen = strlen(a) + 1;
				 int blen = strlen(b) + 1;
				 //AStart = clock();
				 NewH = new int[alen * blen];
				 NewHGPU = new int[alen * blen];
				 //AEnd = clock();

				 

				 //----GPU-----
				 //void NW_GPU(char *Adata, char *Bdata, int alen, int blen, const int r, const int q, int *NewE, int *NewF, int *NewH, clock_t &Begain, clock_t &End);
				 FunctionGPUStart = clock();
				 SM_GPU(a, b, alen, blen, NewHGPU, GPUStart, GPUEnd, CStart, CEnd);
				 FunctionGPUStop = clock();
				 long double Addition = (double)(CEnd - CStart ) / CLOCKS_PER_SEC;				//Get time of memory allocation in GPU
				 long double GPUTime2 = (double)(GPUEnd - GPUStart + FileTime) / CLOCKS_PER_SEC;//Get time of running GPU + memory copy
				 // lblGPU->Text = "GPU Time of function = " + GPUTime2 + " , GPU = " + GPUTime2;

				 {
					 GPUTimes[x] = GPUTime2;
					 Addtionals[x] =Addition;
					 FileTimes[x] =FileTime;
					 Total[x] =  (GPUTime2 + Addition + FileTime);
				 }
//				 richTextBox1->Text += "str1 = " + ptr1 + "\r\nstr2 = " + ptr2 + "\r\nGPU Time : " + GPUTime2 + "\r\n------------\r\n";
				 return((GPUTime2 + Addition + FileTime));
			 }

			 //-----------------------------------------------------------------------------------------------------------------------------
			 //-----------------------------------------------------------------------------------------------------------------------------
			 
			 void Run_Dynamic_NW(String^ pattern)
			 {

				 clock_t s, e;
				 long double Total_GPU = 0;
				 // unsigned int n = thread::hardware_concurrency();
				 s = clock();
				 for (int i = 1; i < listBox1->Items->Count; i++)
				 {
					 String^ d = ProcessFile(listBox1->Items[i]->ToString());
					 listBox2->Items->Add(ProcessFile(listBox1->Items[i]->ToString()));
				 }
				 e = clock();
				 long double Addition = (double)(e + s) / CLOCKS_PER_SEC;
				 lblGPU->Text = "Total GPU = " + Addition;

				 int iCPU = 2;
				 int workers = listBox2->Items->Count / iCPU;
				 omp_set_num_threads(iCPU);
				 int i = 0;
				 GPUTimes = new long double[listBox2->Items->Count];
				 Addtionals = new long double[listBox2->Items->Count];
				 FileTimes = new long double[listBox2->Items->Count];
				 Total = new long double[listBox2->Items->Count];

				 for (int j = 0; j < workers; j += 2)
				 {
#pragma omp parallel
					 {

						 i = omp_get_thread_num() + j;

						 Total_GPU += Run_NW_GPU(0, pattern, listBox2->Items[i]->ToString(), true, i);

					 }
					 Sleep(10);
				 }

				 for (int y = i; y < listBox2->Items->Count; y++)
				 {
					 Total_GPU += Run_NW_GPU(0, pattern, listBox2->Items[y]->ToString(), true, y);
				 }
				 omp_destroy_lock(&my_lock);

				 lblGPU->Text = "Total GPU = " + (Total_GPU + Addition);
				 StreamWriter^ wr = gcnew  StreamWriter("NW_GPU.txt", false);
				 wr->Write("#Qurey Time, Memory allocation , I/O Time , Total\r\n");
				 wr->Close();

				 StreamWriter^ wr1 = gcnew  StreamWriter("NW_GPU.txt", true);
				 String^ temp = "";
				 for (int x = 0; x < listBox2->Items->Count; x++)
				 {
					 if (GPUTimes[x] < 0)
					 {
						 GPUTimes[x] = 0;
					 }

					 if (Addtionals[x] < 0)
					 {
						 Addtionals[x] = 0;
					 }

					 if (FileTimes[x] < 0)
					 {
						 FileTimes[x] = 0;
					 }

					 if (Total[x] < 0)
					 {
						 Total[x] = 0;
					 }
					 temp += GPUTimes[x] + " , " + Addtionals[x] + " , " + FileTimes[x] + " , " + Total[x] + "\r\n";
				 }

				 wr1->Write(temp + lblGPU->Text);
				 wr1->Close();

			 }

			 long double Run_NW_CPU(long double FileTime, String^ ptr1, String^ ptr2, bool file_flag)
			 {

				 StreamWriter^ wr = gcnew  StreamWriter("NW_CPU.txt", file_flag);
				 if (!file_flag)
				 {
					 wr->Write("#Qurey Time, Memory allocation , I/O Time , Total\r\n");
				 }

				 //-----------------------------------------------------
				 clock_t FunctionCPUStart, FunctionCPUStop, CPUStart, CPUEnd;

				 clock_t CStart, CEnd, AStart, AEnd;
				 //-----------------------------------------------------

				 long int LENGHT = MAX(ptr1->Length, ptr2->Length);
				 char *a;
				 char *b;
				 long int t;
				 int *NewH, *NewHGPU;

				 CStart = clock();
				 a = new char[LENGHT];
				 b = new char[LENGHT];
				 CEnd = clock();

				 for (t = 0; t < LENGHT - 1; ++t)
				 {
					 char c1, c2;
					 if (t < ptr1->Length)
					 {
						 c1 = ptr1[t];
					 }
					 else
					 {
						 c1 = '-';
					 }

					 if (t < ptr2->Length)
					 {
						 c2 = ptr2[t];
					 }
					 else
					 {
						 c2 = '-';
					 }
					 a[t] = c1;
					 b[t] = c2;
				 }
				 a[t] = '\0';
				 b[t] = '\0';
				 int alen = strlen(a) + 1;
				 int blen = strlen(b) + 1;
				 AStart = clock();
				 NewH = new int[alen * blen];
				 AEnd = clock();

				 long double Addition = (double)((AEnd + CEnd) - (CStart + AStart)) / CLOCKS_PER_SEC;
				 //----CPU-----
				 // void SM_CPU(char *Adata, char *Bdata, int alen, int blen, int *NewH, clock_t &Begain, clock_t &End);
				 FunctionCPUStart = clock();
				 NW_CPU(a, b, alen, blen, NewH, CPUStart, CPUEnd);
				 FunctionCPUStop = clock();
				 long double CPUTime1 = (double)(FunctionCPUStop - FunctionCPUStart) / CLOCKS_PER_SEC;
				 long double CPUTime2 = (double)(CPUEnd - CPUStart) / CLOCKS_PER_SEC;
				 //lblCPU->Text = "CPU Time of function = " + (CPUTime1 + Addition + FileTime) + " , CPU = " + (CPUTime2 + Addition);
				 //txtDisplay->Text = "H CPU = " + NewH[alen - 1];
				 //------------
				 String^ txt = CPUTime2 + " , " + Addition + " , " + FileTime + " , " + (CPUTime1 + Addition + FileTime).ToString() + "\r\n";
				 wr->Write(txt);
				 wr->Close();
				 richTextBox1->Text += "str1 = " + ptr1 + "\r\nstr2 = " + ptr2 + "\r\nCPU Time : " + CPUTime2 + "\r\n------------\r\n";
				 return((CPUTime1 + Addition + FileTime));
			 }//End Run_NW_CPU

			 long double Run_NW_GPU(long double FileTime, String^ ptr1, String^ ptr2, bool file_flag, int x)
			 {


				 //-----------------------------------------------------
				 // clock_t FunctionCPUStart, FunctionCPUStop, CPUStart, CPUEnd;
				 clock_t FunctionGPUStart, FunctionGPUStop, GPUStart, GPUEnd;

				 clock_t CStart, CEnd, AStart, AEnd;
				 //-----------------------------------------------------

				 long int LENGHT = MAX(ptr1->Length, ptr2->Length);
				 char *a;
				 char *b;
				 long int t;
				 int *NewH, *NewHGPU;

				 //CStart = clock();
				 a = new char[LENGHT];
				 b = new char[LENGHT];
				 // CEnd = clock();

				 for (t = 0; t < LENGHT - 1; ++t)
				 {
					 char c1, c2;
					 if (t < ptr1->Length)
					 {
						 c1 = ptr1[t];
					 }
					 else
					 {
						 c1 = '-';
					 }

					 if (t < ptr2->Length)
					 {
						 c2 = ptr2[t];
					 }
					 else
					 {
						 c2 = '-';
					 }
					 a[t] = c1;
					 b[t] = c2;
					 //printf("Random number: %d, char = %c\n",num,c);
				 }
				 a[t] = '\0';
				 b[t] = '\0';
				 int alen = strlen(a) + 1;
				 int blen = strlen(b) + 1;
				 //AStart = clock();
				 NewH = new int[alen * blen];
				 NewHGPU = new int[alen * blen];
				 //AEnd = clock();



				 //----GPU-----
				 //void NW_GPU(char *Adata, char *Bdata, int alen, int blen, const int r, const int q, int *NewE, int *NewF, int *NewH, clock_t &Begain, clock_t &End);
				 FunctionGPUStart = clock();
				 NW_GPU(a, b, alen, blen, NewHGPU, GPUStart, GPUEnd, CStart, CEnd);
				 FunctionGPUStop = clock();
				 long double Addition = (double)(CEnd - CStart) / CLOCKS_PER_SEC;				//Get time of memory allocation in GPU
				 long double GPUTime2 = (double)(GPUEnd - GPUStart + FileTime) / CLOCKS_PER_SEC;//Get time of running GPU + memory copy
				 // lblGPU->Text = "GPU Time of function = " + GPUTime2 + " , GPU = " + GPUTime2;

				 {
					 GPUTimes[x] = GPUTime2;
					 Addtionals[x] = Addition;
					 FileTimes[x] = FileTime;
					 Total[x] = (GPUTime2 + Addition + FileTime);
				 }
				 //				 richTextBox1->Text += "str1 = " + ptr1 + "\r\nstr2 = " + ptr2 + "\r\nGPU Time : " + GPUTime2 + "\r\n------------\r\n";
				 return((GPUTime2 + Addition + FileTime));
			 }

			 String^ Print(int *H,int L)
			 {
				 String^ Display = " ";
				 for (int r = 0; r < L; r++)
				 {
					 for (int c = 0; c < L; c++)
					 {
						 //printf("Type a number for <line: %d, column: %d>\t", i, j);
						 Display+=H[r *L + c]+"\t";// printf("\n");
					 }
					 Display+="\n";
				 }
				 return Display;
			 }
	};
}
