// EquiposElectricos.cpp : Define el punto de entrada de la aplicación.
//

#include "framework.h"
#include "EquiposElectricos.h"


#define MAX_LOADSTRING 100

// Variables globales:
HINSTANCE hInst;                                // instancia actual
WCHAR szTitle[MAX_LOADSTRING];                  // Texto de la barra de título
WCHAR szWindowClass[MAX_LOADSTRING];            // nombre de clase de la ventana principal

// Declaraciones de funciones adelantadas incluidas en este módulo de código:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK DlgProc1(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK DlgProc2(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK DlgProc3(HWND, UINT, WPARAM, LPARAM);
void GuardarDatosArchivo(MatrixD*);
BOOL CALLBACK DlgProc4(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK DlgProc5(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK DlgProc6(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK DlgProc7(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK DlgProc8(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK DlgProc9(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK DlgProc10(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK DlgProc11(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK DlgProc12(HWND, UINT, WPARAM, LPARAM);
void LeerDatosProyecto(MatrixD*);
BOOL CALLBACK DlgProc13(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK DlgProc14(HWND, UINT, WPARAM, LPARAM);
void CrearProyectoEditar(MatrixD*, MatrixD*);
BOOL CALLBACK ReportePantalla1(HWND, UINT, WPARAM, LPARAM);
BOOL DialogoNombreReporte1(HWND, UINT, WPARAM, LPARAM);
void ReporteArchivo1(MatrixD*);
void DibujarDiagramaVectorial(MatrixD* dat);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Colocar código aquí.

    // Inicializar cadenas globales
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_EQUIPOSELECTRICOS, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Realizar la inicialización de la aplicación:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_EQUIPOSELECTRICOS));

    MSG msg;

    // Bucle principal de mensajes:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNCIÓN: MyRegisterClass()
//  PROPÓSITO: Registra la clase de ventana.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_EQUIPOSELECTRICOS));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_EQUIPOSELECTRICOS);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCIÓN: InitInstance(HINSTANCE, int)
//   PROPÓSITO: Guarda el identificador de instancia y crea la ventana principal
//   COMENTARIOS:
//        En esta función, se guarda el identificador de instancia en una variable común y
//        se crea y muestra la ventana principal del programa.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Almacenar identificador de instancia en una variable global

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCIÓN: WndProc(HWND, UINT, WPARAM, LPARAM)
//  PROPÓSITO: Procesa mensajes de la ventana principal.
//  WM_COMMAND  - procesar el menú de aplicaciones
//  WM_PAINT    - Pintar la ventana principal
//  WM_DESTROY  - publicar un mensaje de salida y volver


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static MatrixD datos;
    static MatrixD* dat = &datos;
    static MatrixD datosE;
    static MatrixD* datE = &datosE;

    wchar_t inform[40] = L"";
    wchar_t* inf = inform;
    wchar_t texto1[160];
            
    switch (message)
    {
    /*case WM_INITDIALOG: {
        MessageBoxW(hWnd, L"Se debe cargar un proyecto existente o crear uno nuevo antes de iniciar el analisis de cualquier equipo", L"CARGA DE DATOS", MB_ICONEXCLAMATION | MB_OK);
    }
    return TRUE;*/
    case WM_COMMAND:{
        int wmId = LOWORD(wParam);

        switch (wmId)
        {
        case IDM_NUEVO: {
            MessageBoxW(hWnd, L"Nuevo Proyecto", L"CARGA DE DATOS", MB_ICONEXCLAMATION | MB_OK);
            dat->abortar = 1;
            DialogBoxParamW(hInst, MAKEINTRESOURCE(IDD_DIALOGBAR), hWnd, (DLGPROC)DlgProc1, (LPARAM)dat);
            dat->Gen.resize(dat->ng, std::vector<double>(20, { 0.0 })); //Inicializa vector de Generadores
            dat->Transf.resize(dat->nt, std::vector<double>(20, { 0.0 })); //Inicializa vector de Transformadores
            dat->Lin.resize(dat->nl, std::vector<double>(20, { 0.0 })); //Inicializa vector de Lineas
            dat->Mot.resize(dat->nm, std::vector<double>(20, { 0.0 })); //Inicializa vector de Motores
            dat->Car.resize(dat->nc, std::vector<double>(20, { 0.0 })); //Inicializa vector de Cargas
        }
        break;

        case IDM_EXISTENTE: {
            MessageBoxW(hWnd, L"Proyecto Existente", L"RESULTADO CORRECTO", MB_ICONEXCLAMATION | MB_OK);
            DialogBoxParamW(hInst, MAKEINTRESOURCE(IDD_DIALOGBAR1), hWnd, (DLGPROC)DlgProc12, (LPARAM)dat);
            fstream arch;
            arch.open(dat->NombreProy);
            int ind = 0;
            if (!arch) {
                cerr << "Error al abrir el archivo de datos del sistema.txt. " << endl;
                MessageBoxW(hWnd, L"El archivo no existe", L"Error", IDOK);
                arch.close();
                break;
            }
            else {
                ind = 1;
            }
            arch.close();
            if (ind == 1) {
                LeerDatosProyecto(dat);
                //printMatrix3(dat, hwnd, hInstance);
                MessageBoxW(hWnd, L"El archivo de datos se cargo exitosamente", L"CARGA DE ARCHIVO", MB_ICONEXCLAMATION | MB_OK);
            }
            break;

        }
        break;

        case IDM_EDITAR: {
            MessageBoxW(hWnd, L"Proyecto a Editar", L"MENU DE EDICION", MB_ICONEXCLAMATION | MB_OK);
            DialogBoxParamW(hInst, MAKEINTRESOURCE(IDD_DIALOGBAR2), hWnd, (DLGPROC)DlgProc13, (LPARAM)dat);
            fstream arch;
            arch.open(dat->NombreProy);
            int ind = 0;
            if (!arch) {
                cerr << "Error al abrir el archivo de datos del sistema.txt. " << endl;
                MessageBoxW(hWnd, L"El archivo no existe", L"Error", IDOK);
                arch.close();
                break;
            }
            else {
                ind = 1;
            }
            arch.close();
            if (ind == 1) {
                LeerDatosProyecto(dat);
                DialogBoxParamW(hInst, MAKEINTRESOURCE(IDD_DIALOGBAR3), hWnd, (DLGPROC)DlgProc14, (LPARAM)dat);
                //printMatrix3(dat, hwnd, hInstance);
                MessageBoxW(hWnd, L"El archivo de datos se cargo exitosamente.  Proceder a la edicion de datos", L"EDICION DE PROYECTO", MB_ICONEXCLAMATION | MB_OK);
            }
            CrearProyectoEditar(dat, datE);
            GuardarDatosArchivo(datE);
            dat = datE;
            break;
        }
        break;

        case IDM_GUARDARPROYECTO: {
            MessageBoxW(hWnd, L"Guardar Proyecto", L"RESULTADO CORRECTO", MB_ICONEXCLAMATION | MB_OK);
            GuardarDatosArchivo(dat);
        }
        break;

        case IDM_GEN1: {
            MessageBoxW(hWnd, L"Analisis PU de Generador", L"CARGA DE DATOS", MB_ICONEXCLAMATION | MB_OK);
            for (int i = 0; i < dat->ng; i++) {
                if (dat->abortar == 0) break;
                swprintf_s(inform, 40, L"Cargar Generador %d", i + 1);
                MessageBoxW(hWnd, inform, L"CARGAR DATOS", MB_OK);
                dat->ind = i;
                DialogBoxParamW(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, (DLGPROC)DlgProc2, (LPARAM)dat);
            }

            MessageBoxW(hWnd, L"Resultado del Analisis PU de Generador", L"RESULTADOS", MB_ICONEXCLAMATION | MB_OK);
            for (int i = 0; i < dat->ng; i++) {
                dat->ind = i;
                DialogBoxParamW(hInst, MAKEINTRESOURCE(IDD_DIALOG2), hWnd, (DLGPROC)DlgProc3, (LPARAM)dat);
            }
        }
        break;

        case ID_GEN_DIAGVECTOR: {
            DibujarDiagramaVectorial(dat);
        }
        break;

        case IDM_TRANSF1: {
            MessageBoxW(hWnd, L"Analisis PU de Transformador", L"RESULTADO CORRECTO", MB_ICONEXCLAMATION | MB_OK);
            for (int i = 0; i < dat->nt; i++) {
                if (dat->abortar == 0) break;
                swprintf_s(inform, 40, L"Cargar Transformador %d", i + 1);
                MessageBoxW(hWnd, inform, L"CARGAR DATOS", MB_OK);
                dat->ind = i;
                DialogBoxParamW(hInst, MAKEINTRESOURCE(IDD_DIALOG3), hWnd, (DLGPROC)DlgProc4, (LPARAM)dat);
            }
            MessageBoxW(hWnd, L"Resultado del Analisis PU de Transformador", L"RESULTADOS", MB_ICONEXCLAMATION | MB_OK);
            for (int i = 0; i < dat->nt; i++) {
                dat->ind = i;
                DialogBoxParamW(hInst, MAKEINTRESOURCE(IDD_DIALOG4), hWnd, (DLGPROC)DlgProc5, (LPARAM)dat);
            }
        }
        break;

        case IDM_LIN1:{
            MessageBoxW(hWnd, L"Analisis PU de Linea", L"RESULTADO CORRECTO", MB_ICONEXCLAMATION | MB_OK);
            for (int i = 0; i < dat->nl; i++) {
                if (dat->abortar == 0) break;
                swprintf_s(inform, 40, L"Cargar Linea %d", i + 1);
                MessageBoxW(hWnd, inform, L"CARGAR DATOS", MB_OK);
                dat->ind = i;
                DialogBoxParamW(hInst, MAKEINTRESOURCE(IDD_DIALOG5), hWnd, (DLGPROC)DlgProc6, (LPARAM)dat);
            }
            MessageBoxW(hWnd, L"Resultado del Analisis PU de Lineas", L"RESULTADOS", MB_ICONEXCLAMATION | MB_OK);
            for (int i = 0; i < dat->nl; i++) {
                dat->ind = i;
                DialogBoxParamW(hInst, MAKEINTRESOURCE(IDD_DIALOG6), hWnd, (DLGPROC)DlgProc7, (LPARAM)dat);
            }
        }
        break;

        case IDM_MOT1: {
            MessageBoxW(hWnd, L"Analisis PU de Motor", L"CARGA DE DATOS", MB_ICONEXCLAMATION | MB_OK);
            for (int i = 0; i < dat->nm; i++) {
                if (dat->abortar == 0) break;
                swprintf_s(inform, 40, L"Cargar Motor %d", i + 1);
                MessageBoxW(hWnd, inform, L"CARGAR DATOS", MB_OK);
                dat->ind = i;
                DialogBoxParamW(hInst, MAKEINTRESOURCE(IDD_DIALOG7), hWnd, (DLGPROC)DlgProc8, (LPARAM)dat);
            }

            MessageBoxW(hWnd, L"Resultado del Analisis PU de Motor", L"RESULTADOS", MB_ICONEXCLAMATION | MB_OK);
            for (int i = 0; i < dat->nm; i++) {
                dat->ind = i;
                DialogBoxParamW(hInst, MAKEINTRESOURCE(IDD_DIALOG8), hWnd, (DLGPROC)DlgProc9, (LPARAM)dat);
            }
        }
        break;

        case IDM_CARGA1: {
            MessageBoxW(hWnd, L"Analisis PU de Carga", L"CARGA DE DATOS", MB_ICONEXCLAMATION | MB_OK);
            for (int i = 0; i < dat->nc; i++) {
                if (dat->abortar == 0) break;
                swprintf_s(inform, 40, L"Cargar Carga SL %d", i + 1);
                MessageBoxW(hWnd, inform, L"CARGAR DATOS", MB_OK);
                dat->ind = i;
                DialogBoxParamW(hInst, MAKEINTRESOURCE(IDD_DIALOG9), hWnd, (DLGPROC)DlgProc10, (LPARAM)dat);
            }

            MessageBoxW(hWnd, L"Resultado del Analisis PU de la Carga", L"RESULTADOS", MB_ICONEXCLAMATION | MB_OK);
            for (int i = 0; i < dat->nc; i++) {
                dat->ind = i;
                DialogBoxParamW(hInst, MAKEINTRESOURCE(IDD_DIALOG10), hWnd, (DLGPROC)DlgProc11, (LPARAM)dat);
            }
        }
        break;

        case IDM_REPORTES_PANTALLA:{
            MessageBoxW(hWnd, L"Reportes por pantalla", L"REPORTE DE RESULTADOS", MB_ICONEXCLAMATION | MB_OK);
            DialogBoxParamW(hInst, MAKEINTRESOURCE(IDD_DIALOG11), hWnd, (DLGPROC)ReportePantalla1, (LPARAM)dat);
        }
        break;

        case IDM_REPORTES_IMPRESOS: {
            MessageBoxW(hWnd, L"Reportes en archivo", L"REPORTE DE RESULTADOS", MB_ICONEXCLAMATION | MB_OK);
            wchar_t NombreReporte1[100] = L"";
            swprintf_s(NombreReporte1, 80, dat->NombreProy, 0L);
            wcscat_s(NombreReporte1, L"_Reporte_1");
            swprintf_s(dat->NombreReporte1, 80, NombreReporte1, 0L);
            DialogBoxParamW(hInst, MAKEINTRESOURCE(IDD_DIALOGBAR4), hWnd, (DLGPROC)DialogoNombreReporte1, (LPARAM)dat);
            ReporteArchivo1(dat);
            MessageBoxW(hWnd, L"Reporte fializado", L"REPORTES", MB_ICONEXCLAMATION | MB_OK);
        }
        break;

        case IDM_ABOUT:{
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
        }
        break;

        case IDM_EXIT:{
            DestroyWindow(hWnd);
        }
        break;

        default:
            return DefWindowProc(hWnd, message, wParam, lParam);  // ✔️ IMPORTANTE
        }  //Fin del switch wmId del command
    }  //Fin del command
    break;
    
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        EndPaint(hWnd, &ps);
    }
    break;

    case WM_DESTROY:{
        PostQuitMessage(0);
    }
    break;
    }  // Fin del switch message

    return DefWindowProc(hWnd, message, wParam, lParam);  // ✔️ CRÍTICO
}


// Controlador de mensajes del cuadro Acerca de.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

 BOOL CALLBACK DlgProc1(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{   //Procedimiento para cargar datos basicos del sistema

    static MatrixD* Datbas;
    

    switch (msg)                  // manipulador del mensaje
    {
    case WM_INITDIALOG:
    {
        Datbas = (MatrixD*)lParam;
        SetDlgItemTextW(hDlg, IDC_EDIT1, (LPCWSTR)Datbas->NombreProy);
        SetDlgItemInt(hDlg, IDC_EDIT2, Datbas->ng, true); //No. de GENERADORES
        SetDlgItemInt(hDlg, IDC_EDIT3, Datbas->nt, true); //No. de TRANSFORMADORES
        SetDlgItemInt(hDlg, IDC_EDIT4, Datbas->nl, true); //No. de LINEAS
        SetDlgItemInt(hDlg, IDC_EDIT5, Datbas->nm, true); //No. de MOTORES
        SetDlgItemInt(hDlg, IDC_EDIT6, Datbas->nc, true); //No. de CARGAS SL
        SetFocus(GetDlgItem(hDlg, IDC_EDIT1));
    }
    return TRUE;
    case WM_COMMAND:
        switch (LOWORD(wParam)) {
        case IDOK: {
            wchar_t varaux1[20] = L"";
            wchar_t* vara = varaux1;
            const char vvv[20] = "";
            BOOL Bnum = false;
            //Captura de los datos del nuevo proyecto;
            GetDlgItemTextW(hDlg, IDC_EDIT1, (LPWSTR)Datbas->NombreProy, 80);
            Datbas->ng = (int)GetDlgItemInt(hDlg, IDC_EDIT2, &Bnum, TRUE);
            Datbas->nt = (int)GetDlgItemInt(hDlg, IDC_EDIT3, &Bnum, TRUE);
            Datbas->nl = (int)GetDlgItemInt(hDlg, IDC_EDIT4, &Bnum, TRUE);
            Datbas->nm = (int)GetDlgItemInt(hDlg, IDC_EDIT5, &Bnum, TRUE);
            Datbas->nc = (int)GetDlgItemInt(hDlg, IDC_EDIT6, &Bnum, TRUE);
            EndDialog(hDlg, IDOK);
        }
        break;
        case IDCANCEL:
        {
            MessageBoxW(hDlg, L"No se cargaron los datos", L"PROCESO TERMINADO", MB_ICONEXCLAMATION | MB_OK);
            Datbas->abortar = 0;
            EndDialog(hDlg, IDCANCEL);
        }
        break;
        }  //Fin del switch del COMMAND
        break;
    }  // Fin del switch del mensaje
    return FALSE;
}

 BOOL CALLBACK DlgProc2(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
 {   //Procedimiento para cargar datos basicos del generador

     static MatrixD* Datbas;


     switch (msg)                  // manipulador del mensaje
     {
     case WM_INITDIALOG:
     {
         Datbas = (MatrixD*)lParam;
         wchar_t texto[10];
         int i = Datbas->ind;
         SetDlgItemTextW(hDlg, IDC_EDIT8, (LPCWSTR)Datbas->NombreProy);
         SetDlgItemInt(hDlg, IDC_EDIT9, Datbas->ng, true); //No. de GENERADORES
         SetDlgItemInt(hDlg, IDC_EDIT1, (i + 1), true); //No. de generador a carga

         swprintf_s(texto, 10, L"%.5f", (float)Datbas->Gen[i][0]);
         SetDlgItemTextW(hDlg, IDC_EDIT2, (LPCWSTR)texto); //MVA base del generador
         swprintf_s(texto, 10, L"%.5f", (float)Datbas->Gen[i][1]);
         SetDlgItemTextW(hDlg, IDC_EDIT3, (LPCWSTR)texto); //Voltaje nominal del generador
         swprintf_s(texto, 10, L"%.5f", (float)Datbas->Gen[i][2]);
         SetDlgItemTextW(hDlg, IDC_EDIT4, (LPCWSTR)texto); //Reactancia sincronica del generador
         swprintf_s(texto, 10, L"%.5f", (float)Datbas->Gen[i][3]);
         SetDlgItemTextW(hDlg, IDC_EDIT5, (LPCWSTR)texto); //Resistencia de armadura del generador
         swprintf_s(texto, 10, L"%.5f", (float)Datbas->Gen[i][4]);
         SetDlgItemTextW(hDlg, IDC_EDIT6, (LPCWSTR)texto); //MVA base Nueva del generador
         swprintf_s(texto, 10, L"%.5f", (float)Datbas->Gen[i][5]);
         SetDlgItemTextW(hDlg, IDC_EDIT7, (LPCWSTR)texto); //Voltaje base Nueva del generador
         
         Generador G;
         if (Datbas->Gen[i][6] == 0) swprintf_s(texto, 10, L"%.5f", (float)G.getMVA()*0.8);
         else  swprintf_s(texto, 10, L"%.5f", (float)Datbas->Gen[i][6]);
         SetDlgItemTextW(hDlg, IDC_EDIT12, (LPCWSTR)texto); //P de operacion del generador
         
         if (Datbas->Gen[i][7] == 0) swprintf_s(texto, 10, L"%.5f", (float)G.getMVA() * 0.6);
         else  swprintf_s(texto, 10, L"%.5f", (float)Datbas->Gen[i][7]);
         SetDlgItemTextW(hDlg, IDC_EDIT18, (LPCWSTR)texto); //Q de operacion del generador
                  
         if (Datbas->Gen[i][8] == 0) swprintf_s(texto, 10, L"%.5f", (float)G.getVn());
         else  swprintf_s(texto, 10, L"%.5f", (float)Datbas->Gen[i][8]);
         SetDlgItemTextW(hDlg, IDC_EDIT19, (LPCWSTR)texto); //V de operacion del generador
                  
         SetFocus(GetDlgItem(hDlg, IDC_EDIT1));
     }
     return TRUE;
     case WM_COMMAND: {
         switch (LOWORD(wParam)) {
         case IDOK: {
             wchar_t varaux1[20] = L"";
             int i = Datbas->ind;

             GetDlgItemTextW(hDlg, IDC_EDIT2, (LPWSTR)varaux1, 10); //MVA base euipo
             Datbas->Gen[i][0] = stof(varaux1);
             GetDlgItemTextW(hDlg, IDC_EDIT3, (LPWSTR)varaux1, 10); //Voltaje base equipo
             Datbas->Gen[i][1] = stof(varaux1);
             GetDlgItemTextW(hDlg, IDC_EDIT4, (LPWSTR)varaux1, 10); //Xd pu base equipo
             Datbas->Gen[i][2] = stof(varaux1);
             GetDlgItemTextW(hDlg, IDC_EDIT5, (LPWSTR)varaux1, 10); //Ra pu base equipo
             Datbas->Gen[i][3] = stof(varaux1);
             GetDlgItemTextW(hDlg, IDC_EDIT6, (LPWSTR)varaux1, 10); //MVA nuevo
             Datbas->Gen[i][4] = stof(varaux1);
             GetDlgItemTextW(hDlg, IDC_EDIT7, (LPWSTR)varaux1, 10); //Vbase nuevo
             Datbas->Gen[i][5] = stof(varaux1);
             GetDlgItemTextW(hDlg, IDC_EDIT12, (LPWSTR)varaux1, 10); //P de operacion
             Datbas->Gen[i][6] = stof(varaux1);
             GetDlgItemTextW(hDlg, IDC_EDIT18, (LPWSTR)varaux1, 10); //Q de operacion
             Datbas->Gen[i][7] = stof(varaux1);
             GetDlgItemTextW(hDlg, IDC_EDIT19, (LPWSTR)varaux1, 10); //V de operacion
             Datbas->Gen[i][8] = stof(varaux1);

             EndDialog(hDlg, FALSE);
         }
         break;
         case IDCANCEL:
         {
             MessageBox(hDlg, L"No se cargaron los datos", L"PROCESO TERMINADO", MB_ICONEXCLAMATION | MB_OK);
             Datbas->abortar = 0;
             EndDialog(hDlg, FALSE);
         }
         break;
         }  //Fin del switch del COMMAND
     }
     break;
     }  // Fin del switch del mensaje
     return FALSE;
 }

 BOOL CALLBACK DlgProc3(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
 {   //Procedimiento para mostrar el resultado del analisis pu de generadores

     static MatrixD* Datbas;


     switch (msg)                  // manipulador del mensaje
     {
     case WM_INITDIALOG:
     {
         Datbas = (MatrixD*)lParam;
         wchar_t texto[80];
         int i = Datbas->ind;
         SetDlgItemTextW(hDlg, IDC_EDIT3, (LPCWSTR)Datbas->NombreProy);
         SetDlgItemInt(hDlg, IDC_EDIT2, Datbas->ng, true); //No. de GENERADORES
         SetDlgItemInt(hDlg, IDC_EDIT1, (i + 1), true); //No. de generador a carga
         
         Generador G(Datbas->Gen[i][0], Datbas->Gen[i][1], Datbas->Gen[i][2], Datbas->Gen[i][3]);
         G.setBaseNueva(Datbas->Gen[i][4], Datbas->Gen[i][5]);
         //G.DiagVectorialGC(Datbas->Gen[i][6], Datbas->Gen[i][7], Datbas->Gen[i][8]);
         
         swprintf_s(texto, 80, L"Sbase = %.5f MVA", (float)G.getMVA());
         SendDlgItemMessage(hDlg, IDC_LIST2, LB_ADDSTRING, 0, (LPARAM)texto); 
         swprintf_s(texto, 80, L"Vbase = %.5f Kv", (float)G.getVn());
         SendDlgItemMessage(hDlg, IDC_LIST2, LB_ADDSTRING, 0, (LPARAM)texto);
         swprintf_s(texto, 80, L"Ibase = Inominal = %.5f Ka", (float)G.getIn());
         SendDlgItemMessage(hDlg, IDC_LIST2, LB_ADDSTRING, 0, (LPARAM)texto);
         swprintf_s(texto, 80, L"Zbase = %.5f Ohm", (float)G.getZb());
         SendDlgItemMessage(hDlg, IDC_LIST2, LB_ADDSTRING, 0, (LPARAM)texto);
         swprintf_s(texto, 80, L"Reactancia Xd en PU, Xd = %.5f PU", (float)G.getXd());
         SendDlgItemMessage(hDlg, IDC_LIST2, LB_ADDSTRING, 0, (LPARAM)texto);
         swprintf_s(texto, 80, L"Reactancia Xd en ohm = %.5f Ohm", (float)G.getXd() * (float)G.getZb());
         SendDlgItemMessage(hDlg, IDC_LIST2, LB_ADDSTRING, 0, (LPARAM)texto);
         swprintf_s(texto, 80, L"Resistencia de armadura en pu Ra = %.5f PU", (float)G.getRa());
         SendDlgItemMessage(hDlg, IDC_LIST2, LB_ADDSTRING, 0, (LPARAM)texto);
         swprintf_s(texto, 80, L"Resistencia de armadura en ohm Ra = %.5f Ohm", (float)G.getRa()*(float)G.getZb());
         SendDlgItemMessage(hDlg, IDC_LIST2, LB_ADDSTRING, 0, (LPARAM)texto);
         

         swprintf_s(texto, 80, L"SbaseNueva = %.5f MVA", (float)G.getMVAN());
         SendDlgItemMessage(hDlg, IDC_LIST3, LB_ADDSTRING, 0, (LPARAM)texto);
         swprintf_s(texto, 80, L"VbaseNueva = %.5f Kv", (float)G.getVbN());
         SendDlgItemMessage(hDlg, IDC_LIST3, LB_ADDSTRING, 0, (LPARAM)texto);
         swprintf_s(texto, 80, L"IbaseNueva = %.5f Ka", (float)G.getIbN());
         SendDlgItemMessage(hDlg, IDC_LIST3, LB_ADDSTRING, 0, (LPARAM)texto);
         swprintf_s(texto, 80, L"ZbaseNueva = %.5f Ohm", (float)G.getZbN());
         SendDlgItemMessage(hDlg, IDC_LIST3, LB_ADDSTRING, 0, (LPARAM)texto);
         swprintf_s(texto, 80, L"Reactancia Xd Nueva en pu XdN = %.5f PU", (float)G.getXdN());
         SendDlgItemMessage(hDlg, IDC_LIST3, LB_ADDSTRING, 0, (LPARAM)texto);
         swprintf_s(texto, 80, L"Reactancia Xd Nueva en ohm XdN = %.5f Ohm", (float)G.getXdN()*(float)G.getZbN());
         SendDlgItemMessage(hDlg, IDC_LIST3, LB_ADDSTRING, 0, (LPARAM)texto);
         swprintf_s(texto, 80, L"Resistencia armadura Ra Nueva en pu RaN = %.5f PU", (float)G.getRaN());
         SendDlgItemMessage(hDlg, IDC_LIST3, LB_ADDSTRING, 0, (LPARAM)texto);
         swprintf_s(texto, 80, L"Resistencia armadura Ra Nueva en ohm RaN = %.5f Ohm", (float)G.getRaN() * (float)G.getZbN());
         SendDlgItemMessage(hDlg, IDC_LIST3, LB_ADDSTRING, 0, (LPARAM)texto);
         
     }
     return TRUE;
     case WM_COMMAND: {
         switch (LOWORD(wParam)) {
         case IDOK: {
             
             EndDialog(hDlg, FALSE);
         }
         break;
         case IDCANCEL:
         {
             EndDialog(hDlg, FALSE);
         }
         break;
         }  //Fin del switch del COMMAND
     }
     break;
     }  // Fin del switch del mensaje
     return FALSE;
 }

 void GuardarDatosArchivo(MatrixD* M) {
     ofstream archivo(M->NombreProy);  //constructor de ofstream
     //archivo << "Nombre del proyecto: " << M.NombreProy << endl;
     //archivo << "Datos Basicos del sistema" << endl;
     //archivo << DatosBase->nb << " " << DatosBase->nr << " " << DatosBase->Mbase << " " << DatosBase->Vbase << " " << DatosBase->NombreProy << endl;
     archivo << M->ng << " " << M->nt << " " << M->nl << " " << M->nm << " " << M->nc << " " << endl;
     //archivo << "Datos de los generadores del sistema" << endl;
     for (int i = 0; i < M->ng; i++) {
         for (int j = 0; j < 20; j++) {
             archivo << M->Gen[i][j] << " ";
         }
         archivo << endl;
     }
     //archivo << "Datos de los transformadores del sistema" << endl;
     for (int i = 0; i < M->nt; i++) {
         for (int j = 0; j < 20; j++) {
             archivo << M->Transf[i][j] << " ";
         }
         archivo << endl;
     }
     //archivo << "Datos de las lineas del sistema" << endl;
     for (int i = 0; i < M->nl; i++) {
         for (int j = 0; j < 20; j++) {
             archivo << M->Lin[i][j] << " ";
         }
         archivo << endl;
     }
     //archivo << "Datos de los motores del sistema" << endl;
     for (int i = 0; i < M->nm; i++) {
         for (int j = 0; j < 20; j++) {
             archivo << M->Mot[i][j] << " ";
         }
         archivo << endl;
     }
     //archivo << "Datos de los cargas del sistema" << endl;
     for (int i = 0; i < M->nc; i++) {
         for (int j = 0; j < 20; j++) {
             archivo << M->Car[i][j] << " ";
         }
         archivo << endl;
     }
     archivo.close();
 }

 BOOL CALLBACK DlgProc4(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
 {   //Procedimiento para cargar datos basicos del transformador

     static MatrixD* Datbas;


     switch (msg)                  // manipulador del mensaje
     {
     case WM_INITDIALOG:
     {
         Datbas = (MatrixD*)lParam;
         wchar_t texto[10];
         int i = Datbas->ind;
         SetDlgItemTextW(hDlg, IDC_EDIT10, (LPCWSTR)Datbas->NombreProy);
         SetDlgItemInt(hDlg, IDC_EDIT11, Datbas->nt, true); //No. de TRANSFORMADORES

         SetDlgItemInt(hDlg, IDC_EDIT1, (i + 1), true); //No. de transformador a carga
         
         swprintf_s(texto, 10, L"%.5f", (float)Datbas->Transf[i][0]);
         SetDlgItemTextW(hDlg, IDC_EDIT2, (LPCWSTR)texto); //MVA base del transformador
         
         swprintf_s(texto, 10, L"%.5f", (float)Datbas->Transf[i][1]);
         SetDlgItemTextW(hDlg, IDC_EDIT3, (LPCWSTR)texto); //Voltaje nominal alta del Tx 
         
         swprintf_s(texto, 10, L"%.5f", (float)Datbas->Transf[i][2]);
         SetDlgItemTextW(hDlg, IDC_EDIT4, (LPCWSTR)texto); //Voltaje nominal baja del Tx
         
         swprintf_s(texto, 10, L"%.5f", (float)Datbas->Transf[i][3]);
         SetDlgItemTextW(hDlg, IDC_EDIT5, (LPCWSTR)texto); //Reactancia del Tx
         
         swprintf_s(texto, 10, L"%.5f", (float)Datbas->Transf[i][4]);
         SetDlgItemTextW(hDlg, IDC_EDIT6, (LPCWSTR)texto); //Resisteencia el Tx
         
         swprintf_s(texto, 10, L"%.5f", (float)Datbas->Transf[i][5]);
         SetDlgItemTextW(hDlg, IDC_EDIT7, (LPCWSTR)texto); //MVA base Nueva del Tx

         swprintf_s(texto, 10, L"%.5f", (float)Datbas->Transf[i][6]);
         SetDlgItemTextW(hDlg, IDC_EDIT8, (LPCWSTR)texto); //Voltaje alta base Nueva del Tx

         swprintf_s(texto, 10, L"%.5f", (float)Datbas->Transf[i][7]);
         SetDlgItemTextW(hDlg, IDC_EDIT9, (LPCWSTR)texto); //Voltaje baja base Nueva del Tx

         SetFocus(GetDlgItem(hDlg, IDC_EDIT10));
     }
     return TRUE;
     case WM_COMMAND: {
         switch (LOWORD(wParam)) {
         case IDOK: {
             wchar_t varaux1[20] = L"";
             int i = Datbas->ind;

             GetDlgItemTextW(hDlg, IDC_EDIT2, (LPWSTR)varaux1, 10); //MVA base Tx
             Datbas->Transf[i][0] = stof(varaux1);
            
             GetDlgItemTextW(hDlg, IDC_EDIT3, (LPWSTR)varaux1, 10); //Vbase alta Tx
             Datbas->Transf[i][1] = stof(varaux1);
             
             GetDlgItemTextW(hDlg, IDC_EDIT4, (LPWSTR)varaux1, 10); //Vbase baja Tx
             Datbas->Transf[i][2] = stof(varaux1);
             
             GetDlgItemTextW(hDlg, IDC_EDIT5, (LPWSTR)varaux1, 10); //Xt pu de Tx
             Datbas->Transf[i][3] = stof(varaux1);

             GetDlgItemTextW(hDlg, IDC_EDIT6, (LPWSTR)varaux1, 10); //Ra pu de Tx
             Datbas->Transf[i][4] = stof(varaux1);

             GetDlgItemTextW(hDlg, IDC_EDIT7, (LPWSTR)varaux1, 10); //Sbase nuevo Tx
             Datbas->Transf[i][5] = stof(varaux1);

             GetDlgItemTextW(hDlg, IDC_EDIT8, (LPWSTR)varaux1, 10); //Vbase alta nuevo Tx
             Datbas->Transf[i][6] = stof(varaux1);

             GetDlgItemTextW(hDlg, IDC_EDIT9, (LPWSTR)varaux1, 10); //Vbase baja nuevo Tx
             Datbas->Transf[i][7] = stof(varaux1);
             
             EndDialog(hDlg, FALSE);
         }
                  break;
         case IDCANCEL:
         {
             MessageBox(hDlg, L"No se cargaron los datos", L"PROCESO TERMINADO", MB_ICONEXCLAMATION | MB_OK);
             Datbas->abortar = 0;
             EndDialog(hDlg, FALSE);
         }
         break;
         }  //Fin del switch del COMMAND
     }
                    break;
     }  // Fin del switch del mensaje
     return FALSE;
 }

 BOOL CALLBACK DlgProc5(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
 {   //Procedimiento para mostrar el resultado del analisis pu de transformadores

     static MatrixD* Datbas;


     switch (msg)                  // manipulador del mensaje
     {
     case WM_INITDIALOG:
     {
         Datbas = (MatrixD*)lParam;
         wchar_t texto[90];
         int i = Datbas->ind;
         SetDlgItemTextW(hDlg, IDC_EDIT3, (LPCWSTR)Datbas->NombreProy);
         SetDlgItemInt(hDlg, IDC_EDIT2, Datbas->nt, true); //No. de transformadores
         SetDlgItemInt(hDlg, IDC_EDIT1, (i + 1), true); //No. de transformador a carga

         Transformador T(Datbas->Transf[i][0], Datbas->Transf[i][1], Datbas->Transf[i][2], Datbas->Transf[i][3], Datbas->Transf[i][4]);
         T.setBaseNueva(Datbas->Transf[i][5], Datbas->Transf[i][6], Datbas->Transf[i][7]);

         swprintf_s(texto, 90, L"Sbase = %.5f MVA", (float)T.getMVA());
         SendDlgItemMessage(hDlg, IDC_LIST2, LB_ADDSTRING, 0, (LPARAM)texto);
         swprintf_s(texto, 90, L"Vnom Alta = %.5f Kv", (float)T.getVnA());
         SendDlgItemMessage(hDlg, IDC_LIST2, LB_ADDSTRING, 0, (LPARAM)texto);
         swprintf_s(texto, 90, L"Vnom Baja = %.5f Kv", (float)T.getVnB());
         SendDlgItemMessage(hDlg, IDC_LIST2, LB_ADDSTRING, 0, (LPARAM)texto);
         swprintf_s(texto, 90, L"Ibase Alta = %.5f Ka", (float)T.getInA());
         SendDlgItemMessage(hDlg, IDC_LIST2, LB_ADDSTRING, 0, (LPARAM)texto);
         swprintf_s(texto, 90, L"Ibase Baja = %.5f Ka", (float)T.getInB());
         SendDlgItemMessage(hDlg, IDC_LIST2, LB_ADDSTRING, 0, (LPARAM)texto);
         swprintf_s(texto, 90, L"Zbase Alta = %.5f Ohm", (float)T.getZbA());
         SendDlgItemMessage(hDlg, IDC_LIST2, LB_ADDSTRING, 0, (LPARAM)texto);
         swprintf_s(texto, 90, L"Zbase Baja = %.5f Ohm", (float)T.getZbB());
         SendDlgItemMessage(hDlg, IDC_LIST2, LB_ADDSTRING, 0, (LPARAM)texto);
         swprintf_s(texto, 90, L"Reactancia en pu Xt = %.5f PU", (float)T.getXt());
         SendDlgItemMessage(hDlg, IDC_LIST2, LB_ADDSTRING, 0, (LPARAM)texto);
         swprintf_s(texto, 90, L"Reactancia de dispersion en ohm referida al lado de alta XtA = %.5f Ohm", (float)T.getXtA());
         SendDlgItemMessage(hDlg, IDC_LIST2, LB_ADDSTRING, 0, (LPARAM)texto);
         swprintf_s(texto, 90, L"Reactancia de dispersion en ohm referida al lado de baja XtB = %.5f Ohm", (float)T.getXtB());
         SendDlgItemMessage(hDlg, IDC_LIST2, LB_ADDSTRING, 0, (LPARAM)texto);
         swprintf_s(texto, 90, L"Resistencia de devanados en pu Rt = %.5f PU", (float)T.getRt());
         SendDlgItemMessage(hDlg, IDC_LIST2, LB_ADDSTRING, 0, (LPARAM)texto);
         swprintf_s(texto, 90, L"Resistencia de devanados en ohm referida al lado de alta RtA = %.5f Ohm", (float)T.getRtA());
         SendDlgItemMessage(hDlg, IDC_LIST2, LB_ADDSTRING, 0, (LPARAM)texto);
         swprintf_s(texto, 90, L"Resistencia de devanados en ohm referida al lado de baja RtA = %.5f Ohm", (float)T.getRtB());
         SendDlgItemMessage(hDlg, IDC_LIST2, LB_ADDSTRING, 0, (LPARAM)texto);
         
         swprintf_s(texto, 90, L"Sbase nueva = %.5f MVA", (float)T.getMVAN());
         SendDlgItemMessage(hDlg, IDC_LIST3, LB_ADDSTRING, 0, (LPARAM)texto);
         swprintf_s(texto, 90, L"Vbase nueva Alta VbAN = %.5f Kv", (float)T.getVnAN());
         SendDlgItemMessage(hDlg, IDC_LIST3, LB_ADDSTRING, 0, (LPARAM)texto);
         swprintf_s(texto, 90, L"Vbase nueva Baja VbBN= %.5f Kv", (float)T.getVnBN());
         SendDlgItemMessage(hDlg, IDC_LIST3, LB_ADDSTRING, 0, (LPARAM)texto);
         swprintf_s(texto, 90, L"Ibase nueva Alta = %.5f Ka", (float)T.getIbAN());
         SendDlgItemMessage(hDlg, IDC_LIST3, LB_ADDSTRING, 0, (LPARAM)texto);
         swprintf_s(texto, 90, L"Ibase nueva Baja = %.5f Ka", (float)T.getIbBN());
         SendDlgItemMessage(hDlg, IDC_LIST3, LB_ADDSTRING, 0, (LPARAM)texto);
         swprintf_s(texto, 90, L"Zbase nueva Alta = %.5f Ohm", (float)T.getZbAN());
         SendDlgItemMessage(hDlg, IDC_LIST3, LB_ADDSTRING, 0, (LPARAM)texto);
         swprintf_s(texto, 90, L"Zbase nueva Baja = %.5f Ohm", (float)T.getZbBN());
         SendDlgItemMessage(hDlg, IDC_LIST3, LB_ADDSTRING, 0, (LPARAM)texto);
         swprintf_s(texto, 90, L"Reactancia nueva en pu XtN = %.5f PU", (float)T.getXtN());
         SendDlgItemMessage(hDlg, IDC_LIST3, LB_ADDSTRING, 0, (LPARAM)texto);
         swprintf_s(texto, 90, L"Reactancia de dispersion nueva en ohm referida al lado de alta XtAN = %.5f Ohm", (float)T.getXtAN());
         SendDlgItemMessage(hDlg, IDC_LIST3, LB_ADDSTRING, 0, (LPARAM)texto);
         swprintf_s(texto, 90, L"Reactancia de dispersion nueva en ohm referida al lado de baja XtBN = %.5f Ohm", (float)T.getXtBN());
         SendDlgItemMessage(hDlg, IDC_LIST3, LB_ADDSTRING, 0, (LPARAM)texto);
         swprintf_s(texto, 90, L"Resistencia de devanados nueva en pu Rt = %.5f PU", (float)T.getRtN());
         SendDlgItemMessage(hDlg, IDC_LIST3, LB_ADDSTRING, 0, (LPARAM)texto);
         swprintf_s(texto, 90, L"Resistencia de devanados nueva en ohm referida al lado de alta RtA = %.5f Ohm", (float)T.getRtAN());
         SendDlgItemMessage(hDlg, IDC_LIST3, LB_ADDSTRING, 0, (LPARAM)texto);
         swprintf_s(texto, 90, L"Resistencia de devanados nueva en ohm referida al lado de baja RtA = %.5f Ohm", (float)T.getRtBN());
         SendDlgItemMessage(hDlg, IDC_LIST3, LB_ADDSTRING, 0, (LPARAM)texto);

     }
     return TRUE;
     case WM_COMMAND: {
         switch (LOWORD(wParam)) {
         case IDOK: {
         EndDialog(hDlg, FALSE);
         }
         break;
         case IDCANCEL:
         {
             EndDialog(hDlg, FALSE);
         }
         break;
         }  //Fin del switch del COMMAND
     }
                    break;
     }  // Fin del switch del mensaje
     return FALSE;
 }

 BOOL CALLBACK DlgProc6(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
 {   //Procedimiento para cargar datos basicos de las lineas

     static MatrixD* Datbas;


     switch (msg)                  // manipulador del mensaje
     {
     case WM_INITDIALOG:
     {
         Datbas = (MatrixD*)lParam;
         wchar_t texto[10];
         int i = Datbas->ind;
         SetDlgItemTextW(hDlg, IDC_EDIT8, (LPCWSTR)Datbas->NombreProy);
         SetDlgItemInt(hDlg, IDC_EDIT9, Datbas->nl, true); //No. de LINEAS
         SetDlgItemInt(hDlg, IDC_EDIT1, (i + 1), true); //No. de LINEA a carga
         
         swprintf_s(texto, 10, L"%.5f", (float)Datbas->Lin[i][0]);
         SetDlgItemTextW(hDlg, IDC_EDIT2, (LPCWSTR)texto); //Reactancia de la linea
         swprintf_s(texto, 10, L"%.5f", (float)Datbas->Lin[i][1]);
         SetDlgItemTextW(hDlg, IDC_EDIT3, (LPCWSTR)texto); //Resistencia de la linea
         
         swprintf_s(texto, 10, L"%.5f", (float)Datbas->Lin[i][2]);
         SetDlgItemTextW(hDlg, IDC_EDIT6, (LPCWSTR)texto); //MVA base de la linea
         swprintf_s(texto, 10, L"%.5f", (float)Datbas->Lin[i][3]);
         SetDlgItemTextW(hDlg, IDC_EDIT7, (LPCWSTR)texto); //Voltaje base de la linea

         SetFocus(GetDlgItem(hDlg, IDC_EDIT1));
     }
     return TRUE;
     case WM_COMMAND: {
         switch (LOWORD(wParam)) {
         case IDOK: {
             wchar_t varaux1[20] = L"";
             int i = Datbas->ind;

             GetDlgItemTextW(hDlg, IDC_EDIT2, (LPWSTR)varaux1, 10); //Reactancia de la linea
             Datbas->Lin[i][0] = stof(varaux1);
             GetDlgItemTextW(hDlg, IDC_EDIT3, (LPWSTR)varaux1, 10); //Resistencia de la linea
             Datbas->Lin[i][1] = stof(varaux1);
             GetDlgItemTextW(hDlg, IDC_EDIT6, (LPWSTR)varaux1, 10); //MVA base de la linea
             Datbas->Lin[i][2] = stof(varaux1);
             GetDlgItemTextW(hDlg, IDC_EDIT7, (LPWSTR)varaux1, 10); //Voltaje base de la linea
             Datbas->Lin[i][3] = stof(varaux1);

             EndDialog(hDlg, FALSE);
         }
                  break;
         case IDCANCEL:
         {
             MessageBox(hDlg, L"No se cargaron los datos", L"PROCESO TERMINADO", MB_ICONEXCLAMATION | MB_OK);
             Datbas->abortar = 0;
             EndDialog(hDlg, FALSE);
         }
         break;
         }  //Fin del switch del COMMAND
     }
                    break;
     }  // Fin del switch del mensaje
     return FALSE;
 }

 BOOL CALLBACK DlgProc7(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
 {   //Procedimiento para mostrar el resultado del analisis pu de lineas

     static MatrixD* Datbas;


     switch (msg)                  // manipulador del mensaje
     {
     case WM_INITDIALOG:
     {
         Datbas = (MatrixD*)lParam;
         wchar_t texto[80];
         int i = Datbas->ind;
         SetDlgItemTextW(hDlg, IDC_EDIT3, (LPCWSTR)Datbas->NombreProy);
         SetDlgItemInt(hDlg, IDC_EDIT2, Datbas->nl, true); //No. de LINEAS
         SetDlgItemInt(hDlg, IDC_EDIT1, (i + 1), true); //No. de linea a carga
                  
         Linea L(Datbas->Lin[i][2], Datbas->Lin[i][3], Datbas->Lin[i][0], Datbas->Lin[i][1]);
         
         swprintf_s(texto, 80, L"Sbase = %.5f MVA", (float)L.getMVAb());
         SendDlgItemMessage(hDlg, IDC_LIST2, LB_ADDSTRING, 0, (LPARAM)texto);
         swprintf_s(texto, 80, L"Vbase = %.5f Kv", (float)L.getVb());
         SendDlgItemMessage(hDlg, IDC_LIST2, LB_ADDSTRING, 0, (LPARAM)texto);
         swprintf_s(texto, 80, L"Ibase = %.5f Ka", (float)L.getIb());
         SendDlgItemMessage(hDlg, IDC_LIST2, LB_ADDSTRING, 0, (LPARAM)texto);
         swprintf_s(texto, 80, L"Zbase = %.5f Ohm", (float)L.getZb());
         SendDlgItemMessage(hDlg, IDC_LIST2, LB_ADDSTRING, 0, (LPARAM)texto);
         swprintf_s(texto, 80, L"XL(React de linea) en ohm = %.5f Ohm", (float)L.getXL());
         SendDlgItemMessage(hDlg, IDC_LIST2, LB_ADDSTRING, 0, (LPARAM)texto);
         swprintf_s(texto, 80, L"XL(React de linea) en pu = %.5f PU", (float)L.getXpu());
         SendDlgItemMessage(hDlg, IDC_LIST2, LB_ADDSTRING, 0, (LPARAM)texto);
         swprintf_s(texto, 80, L"RL(Resist de linea) = %.5f Ohm", (float)L.getRL());
         SendDlgItemMessage(hDlg, IDC_LIST2, LB_ADDSTRING, 0, (LPARAM)texto);
         swprintf_s(texto, 80, L"RL(Resist de linea) = %.5f PU", (float)L.getRpu());
         SendDlgItemMessage(hDlg, IDC_LIST2, LB_ADDSTRING, 0, (LPARAM)texto);
         
     }
     return TRUE;
     case WM_COMMAND: {
         switch (LOWORD(wParam)) {
         case IDOK: {

             EndDialog(hDlg, FALSE);
         }
                  break;
         case IDCANCEL:
         {
             EndDialog(hDlg, FALSE);
         }
         break;
         }  //Fin del switch del COMMAND
     }
                    break;
     }  // Fin del switch del mensaje
     return FALSE;
 }

 BOOL CALLBACK DlgProc8(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
 {   //Procedimiento para cargar datos basicos del motor

     static MatrixD* Datbas;


     switch (msg)                  // manipulador del mensaje
     {
     case WM_INITDIALOG:
     {
         Datbas = (MatrixD*)lParam;
         wchar_t texto[10];
         int i = Datbas->ind;
         SetDlgItemTextW(hDlg, IDC_EDIT8, (LPCWSTR)Datbas->NombreProy);
         SetDlgItemInt(hDlg, IDC_EDIT9, Datbas->nm, true); //No. de MOTORES

         SetDlgItemInt(hDlg, IDC_EDIT1, (i + 1), true); //No. de motor a carga
         swprintf_s(texto, 10, L"%.5f", (float)Datbas->Mot[i][0]);
         SetDlgItemTextW(hDlg, IDC_EDIT2, (LPCWSTR)texto); //MVA base del motor
         swprintf_s(texto, 10, L"%.5f", (float)Datbas->Mot[i][1]);
         SetDlgItemTextW(hDlg, IDC_EDIT3, (LPCWSTR)texto); //Voltaje nominal del motor
         swprintf_s(texto, 10, L"%.5f", (float)Datbas->Mot[i][2]);
         SetDlgItemTextW(hDlg, IDC_EDIT4, (LPCWSTR)texto); //Reactancia sincronica del motor
         swprintf_s(texto, 10, L"%.5f", (float)Datbas->Mot[i][3]);
         SetDlgItemTextW(hDlg, IDC_EDIT5, (LPCWSTR)texto); //Resistencia de armadura del motor
         swprintf_s(texto, 10, L"%.5f", (float)Datbas->Mot[i][4]);
         SetDlgItemTextW(hDlg, IDC_EDIT6, (LPCWSTR)texto); //MVA base Nueva del motor
         swprintf_s(texto, 10, L"%.5f", (float)Datbas->Mot[i][5]);
         SetDlgItemTextW(hDlg, IDC_EDIT7, (LPCWSTR)texto); //Voltaje base Nueva del motor

         SetFocus(GetDlgItem(hDlg, IDC_EDIT1));
     }
     return TRUE;
     case WM_COMMAND: {
         switch (LOWORD(wParam)) {
         case IDOK: {
             wchar_t varaux1[20] = L"";
             int i = Datbas->ind;

             GetDlgItemTextW(hDlg, IDC_EDIT2, (LPWSTR)varaux1, 10); //MVA base euipo
             Datbas->Mot[i][0] = stof(varaux1);
             GetDlgItemTextW(hDlg, IDC_EDIT3, (LPWSTR)varaux1, 10); //Voltaje base equipo
             Datbas->Mot[i][1] = stof(varaux1);
             GetDlgItemTextW(hDlg, IDC_EDIT4, (LPWSTR)varaux1, 10); //Xd pu base equipo
             Datbas->Mot[i][2] = stof(varaux1);
             GetDlgItemTextW(hDlg, IDC_EDIT5, (LPWSTR)varaux1, 10); //Ra pu base equipo
             Datbas->Mot[i][3] = stof(varaux1);
             GetDlgItemTextW(hDlg, IDC_EDIT6, (LPWSTR)varaux1, 10); //MVA nuevo
             Datbas->Mot[i][4] = stof(varaux1);
             GetDlgItemTextW(hDlg, IDC_EDIT7, (LPWSTR)varaux1, 10); //Vbase nuevo
             Datbas->Mot[i][5] = stof(varaux1);
                          
             EndDialog(hDlg, FALSE);
         }
                  break;
         case IDCANCEL:
         {
             MessageBox(hDlg, L"No se cargaron los datos", L"PROCESO TERMINADO", MB_ICONEXCLAMATION | MB_OK);
             Datbas->abortar = 0;
             EndDialog(hDlg, FALSE);
         }
         break;
         }  //Fin del switch del COMMAND
     }
                    break;
     }  // Fin del switch del mensaje
     return FALSE;
 }

 BOOL CALLBACK DlgProc9(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
 {   //Procedimiento para mostrar el resultado del analisis pu de motores

     static MatrixD* Datbas;


     switch (msg)                  // manipulador del mensaje
     {
     case WM_INITDIALOG:
     {
         Datbas = (MatrixD*)lParam;
         wchar_t texto[80];
         int i = Datbas->ind;
         SetDlgItemTextW(hDlg, IDC_EDIT3, (LPCWSTR)Datbas->NombreProy);
         SetDlgItemInt(hDlg, IDC_EDIT2, Datbas->ng, true); //No. de MOTORES
         SetDlgItemInt(hDlg, IDC_EDIT1, (i + 1), true); //No. de Motor a carga

         Generador M(Datbas->Mot[i][0], Datbas->Mot[i][1], Datbas->Mot[i][2], Datbas->Mot[i][3]);
         M.setBaseNueva(Datbas->Mot[i][4], Datbas->Mot[i][5]);
         
         swprintf_s(texto, 80, L"Sbase = %.5f MVA", (float)M.getMVA());
         SendDlgItemMessage(hDlg, IDC_LIST2, LB_ADDSTRING, 0, (LPARAM)texto);
         swprintf_s(texto, 80, L"Vbase = %.5f Kv", (float)M.getVn());
         SendDlgItemMessage(hDlg, IDC_LIST2, LB_ADDSTRING, 0, (LPARAM)texto);
         swprintf_s(texto, 80, L"Ibase = %.5f Ka", (float)M.getIn());
         SendDlgItemMessage(hDlg, IDC_LIST2, LB_ADDSTRING, 0, (LPARAM)texto);
         swprintf_s(texto, 80, L"Zbase = %.5f Ohm", (float)M.getZb());
         SendDlgItemMessage(hDlg, IDC_LIST2, LB_ADDSTRING, 0, (LPARAM)texto);
         swprintf_s(texto, 80, L"Xd(sincronica) en pu = %.5f PU", (float)M.getXd());
         SendDlgItemMessage(hDlg, IDC_LIST2, LB_ADDSTRING, 0, (LPARAM)texto);
         swprintf_s(texto, 80, L"Xd(sincronica) en ohm = %.5f Ohm", (float)M.getXd() * M.getZb());
         SendDlgItemMessage(hDlg, IDC_LIST2, LB_ADDSTRING, 0, (LPARAM)texto);
         swprintf_s(texto, 80, L"Ra (armadura) en pu = %.5f PU", (float)M.getRa());
         SendDlgItemMessage(hDlg, IDC_LIST2, LB_ADDSTRING, 0, (LPARAM)texto);
         swprintf_s(texto, 80, L"Ra (armadura) en ohm = %.5f Ohm", (float)M.getRa() * M.getZb());
         SendDlgItemMessage(hDlg, IDC_LIST2, LB_ADDSTRING, 0, (LPARAM)texto);

         swprintf_s(texto, 80, L"SbaseNueva = %.5f MVA", (float)M.getMVAN());
         SendDlgItemMessage(hDlg, IDC_LIST3, LB_ADDSTRING, 0, (LPARAM)texto);
         swprintf_s(texto, 80, L"VbaseNueva = %.5f Kv", (float)M.getVbN());
         SendDlgItemMessage(hDlg, IDC_LIST3, LB_ADDSTRING, 0, (LPARAM)texto);
         swprintf_s(texto, 80, L"IbaseNueva = %.5f Ka", (float)M.getIbN());
         SendDlgItemMessage(hDlg, IDC_LIST3, LB_ADDSTRING, 0, (LPARAM)texto);
         swprintf_s(texto, 80, L"ZbaseNueva = %.5f Ohm", (float)M.getZbN());
         SendDlgItemMessage(hDlg, IDC_LIST3, LB_ADDSTRING, 0, (LPARAM)texto);
         swprintf_s(texto, 80, L"XdNueva (sincronica) en pu = %.5f PU", (float)M.getXdN());
         SendDlgItemMessage(hDlg, IDC_LIST3, LB_ADDSTRING, 0, (LPARAM)texto);
         swprintf_s(texto, 80, L"XdNueva (sincronica) en ohm= %.5f Ohm", (float)M.getXdN() * (float)M.getZbN());
         SendDlgItemMessage(hDlg, IDC_LIST3, LB_ADDSTRING, 0, (LPARAM)texto);
         swprintf_s(texto, 80, L"RaNueva (armadura) en pu = %.5f PU", (float)M.getRa());
         SendDlgItemMessage(hDlg, IDC_LIST3, LB_ADDSTRING, 0, (LPARAM)texto);
         swprintf_s(texto, 80, L"RaNueva (armadura) en ohm = %.5f Ohm", (float)M.getRa() * (float)M.getZbN());
         SendDlgItemMessage(hDlg, IDC_LIST3, LB_ADDSTRING, 0, (LPARAM)texto);
                 
     }
     return TRUE;
     case WM_COMMAND: {
         switch (LOWORD(wParam)) {
         case IDOK: {

             EndDialog(hDlg, FALSE);
         }
                  break;
         case IDCANCEL:
         {
             EndDialog(hDlg, FALSE);
         }
         break;
         }  //Fin del switch del COMMAND
     }
                    break;
     }  // Fin del switch del mensaje
     return FALSE;
 }

 BOOL CALLBACK DlgProc10(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
 {   //Procedimiento para cargar datos basicos de las cargas SL

     static MatrixD* Datbas;


     switch (msg)                  // manipulador del mensaje
     {
     case WM_INITDIALOG:
     {
         Datbas = (MatrixD*)lParam;
         wchar_t texto[10];
         int i = Datbas->ind;
         SetDlgItemTextW(hDlg, IDC_EDIT8, (LPCWSTR)Datbas->NombreProy);
         SetDlgItemInt(hDlg, IDC_EDIT9, Datbas->nc, true); //No. de CARGAS SL

         SetDlgItemInt(hDlg, IDC_EDIT1, (i + 1), true); //No. de LINEA a cargar
         swprintf_s(texto, 10, L"%.5f", (float)Datbas->Car[i][0]);
         SetDlgItemTextW(hDlg, IDC_EDIT2, (LPCWSTR)texto); //PL de la carga
         swprintf_s(texto, 10, L"%.5f", (float)Datbas->Car[i][1]);
         SetDlgItemTextW(hDlg, IDC_EDIT3, (LPCWSTR)texto); //QL de la carga
         swprintf_s(texto, 10, L"%.5f", (float)Datbas->Car[i][2]);
         SetDlgItemTextW(hDlg, IDC_EDIT4, (LPCWSTR)texto); //QL de la carga
         swprintf_s(texto, 10, L"%.5f", (float)Datbas->Car[i][3]);
         SetDlgItemTextW(hDlg, IDC_EDIT6, (LPCWSTR)texto); //MVA base de la carga
         swprintf_s(texto, 10, L"%.5f", (float)Datbas->Car[i][4]);
         SetDlgItemTextW(hDlg, IDC_EDIT7, (LPCWSTR)texto); //Voltaje base de la carga

         SetFocus(GetDlgItem(hDlg, IDC_EDIT1));
     }
     return TRUE;
     case WM_COMMAND: {
         switch (LOWORD(wParam)) {
         case IDOK: {
             wchar_t varaux1[20] = L"";
             int i = Datbas->ind;

             GetDlgItemTextW(hDlg, IDC_EDIT2, (LPWSTR)varaux1, 10); //PL
             Datbas->Car[i][0] = stof(varaux1);
             GetDlgItemTextW(hDlg, IDC_EDIT3, (LPWSTR)varaux1, 10); //QL
             Datbas->Car[i][1] = stof(varaux1);
             GetDlgItemTextW(hDlg, IDC_EDIT4, (LPWSTR)varaux1, 10); //VLn
             Datbas->Car[i][2] = stof(varaux1);
             GetDlgItemTextW(hDlg, IDC_EDIT6, (LPWSTR)varaux1, 10); //MVA base de la linea
             Datbas->Car[i][3] = stof(varaux1);
             GetDlgItemTextW(hDlg, IDC_EDIT7, (LPWSTR)varaux1, 10); //Voltaje base de la linea
             Datbas->Car[i][4] = stof(varaux1);
             
             EndDialog(hDlg, FALSE);
         }
                  break;
         case IDCANCEL:
         {
             MessageBox(hDlg, L"No se cargaron los datos", L"PROCESO TERMINADO", MB_ICONEXCLAMATION | MB_OK);
             Datbas->abortar = 0;
             EndDialog(hDlg, FALSE);
         }
         break;
         }  //Fin del switch del COMMAND
     }
                    break;
     }  // Fin del switch del mensaje
     return FALSE;
 }

 BOOL CALLBACK DlgProc11(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
 {   //Procedimiento para mostrar el resultado del analisis pu de cargas SL

     static MatrixD* Datbas;


     switch (msg)                  // manipulador del mensaje
     {
     case WM_INITDIALOG:
     {
         Datbas = (MatrixD*)lParam;
         wchar_t texto[80];
         int i = Datbas->ind;
         SetDlgItemTextW(hDlg, IDC_EDIT3, (LPCWSTR)Datbas->NombreProy);
         SetDlgItemInt(hDlg, IDC_EDIT2, Datbas->nc, true); //No. de CARGAS SL
         SetDlgItemInt(hDlg, IDC_EDIT1, (i + 1), true); //No. de carga SL a cargaar
         
         Carga SL(Datbas->Car[i][0], Datbas->Car[i][1], Datbas->Car[i][2], Datbas->Car[i][3], Datbas->Car[i][4]);
         
         swprintf_s(texto, 80, L"S base de la carga Sbase = %.5f MVA", (float)SL.getSbase());
         SendDlgItemMessage(hDlg, IDC_LIST2, LB_ADDSTRING, 0, (LPARAM)texto);
         swprintf_s(texto, 80, L"V base de la carga Vbase = %.5f Kv", (float)SL.getVbase());
         SendDlgItemMessage(hDlg, IDC_LIST2, LB_ADDSTRING, 0, (LPARAM)texto);
         swprintf_s(texto, 80, L"I base de la carga Ibase = %.5f KA", (float)SL.getIbase());
         SendDlgItemMessage(hDlg, IDC_LIST2, LB_ADDSTRING, 0, (LPARAM)texto);
         swprintf_s(texto, 80, L"Z base de la carga Zbase = %.5f Ohm", (float)SL.getZbase());
         SendDlgItemMessage(hDlg, IDC_LIST2, LB_ADDSTRING, 0, (LPARAM)texto);
         swprintf_s(texto, 80, L"Potencia activa PL = %.5f Wats", (float)SL.getPL());
         SendDlgItemMessage(hDlg, IDC_LIST2, LB_ADDSTRING, 0, (LPARAM)texto);
         swprintf_s(texto, 80, L"Potencia reactiva QL = %.5f MVAR", (float)SL.getQL());
         SendDlgItemMessage(hDlg, IDC_LIST2, LB_ADDSTRING, 0, (LPARAM)texto);
         swprintf_s(texto, 80, L"SL compleja = (%.5f + j %.5f) MVA", (float)real(SL.getSL()), (float)imag(SL.getSL()));
         SendDlgItemMessage(hDlg, IDC_LIST2, LB_ADDSTRING, 0, (LPARAM)texto);
         swprintf_s(texto, 80, L"SL polar = (%.5f /__ %.5f) MVA (angulo en rad)", (float)abs(SL.getSL()), (float)arg(SL.getSL()));
         SendDlgItemMessage(hDlg, IDC_LIST2, LB_ADDSTRING, 0, (LPARAM)texto);
         swprintf_s(texto, 80, L"SL polar = (%.5f /__ %.5f) MVA (angulo en grados)", (float)abs(SL.getSL()), (float)arg(SL.getSL())*180/M_PI);
         SendDlgItemMessage(hDlg, IDC_LIST2, LB_ADDSTRING, 0, (LPARAM)texto);
         swprintf_s(texto, 80, L"SLpu en pu = (%.5f + j %.5f) PU", (float)real(SL.getSLpu()), (float)imag(SL.getSLpu()));
         SendDlgItemMessage(hDlg, IDC_LIST2, LB_ADDSTRING, 0, (LPARAM)texto);
         swprintf_s(texto, 80, L"SLpu en pu = (%.5f /_ %.5f) PU (angulo en rad)", (float)abs(SL.getSLpu()), (float)arg(SL.getSLpu()));
         SendDlgItemMessage(hDlg, IDC_LIST2, LB_ADDSTRING, 0, (LPARAM)texto);
         swprintf_s(texto, 80, L"SLpu en pu = (%.5f /_ %.5f) PU (angulo en grados)", (float)abs(SL.getSLpu()), (float)arg(SL.getSLpu())*180/M_PI);
         SendDlgItemMessage(hDlg, IDC_LIST2, LB_ADDSTRING, 0, (LPARAM)texto);
         swprintf_s(texto, 80, L"Voltaje de carga VLn = %.5f Kv", (float)SL.getVLn());
         SendDlgItemMessage(hDlg, IDC_LIST2, LB_ADDSTRING, 0, (LPARAM)texto);
         swprintf_s(texto, 80, L"Voltaje en pu VLnpu = %.5f PU", (float)SL.getVLnpu());
         SendDlgItemMessage(hDlg, IDC_LIST2, LB_ADDSTRING, 0, (LPARAM)texto);
         swprintf_s(texto, 80, L"Angulo del FP de la carga AngFP = %.5f radianes", (float)SL.getAngFP());
         SendDlgItemMessage(hDlg, IDC_LIST2, LB_ADDSTRING, 0, (LPARAM)texto);
         swprintf_s(texto, 80, L"Angulo del FP de la carga AngFPGr = %.5f grados", (float)SL.getAngFPGr());
         SendDlgItemMessage(hDlg, IDC_LIST2, LB_ADDSTRING, 0, (LPARAM)texto);
         swprintf_s(texto, 80, L"Factor de potencia de la carga FP = %.5f  en %ls", (float)SL.getFP(), SL.gettipoFP());
         SendDlgItemMessage(hDlg, IDC_LIST2, LB_ADDSTRING, 0, (LPARAM)texto);
         swprintf_s(texto, 80, L"IL compleja = (%.5f + j %.5f) KA", (float)real(SL.getIL()), (float)imag(SL.getIL()));
         SendDlgItemMessage(hDlg, IDC_LIST2, LB_ADDSTRING, 0, (LPARAM)texto);
         swprintf_s(texto, 80, L"IL polar = %.5f /__ %.5f KA", (float)abs(SL.getIL()), (float)arg(SL.getIL()));
         SendDlgItemMessage(hDlg, IDC_LIST2, LB_ADDSTRING, 0, (LPARAM)texto);
         swprintf_s(texto, 80, L"IL Angulo(rad) = %.5f radianes", (float)arg(SL.getIL()));
         SendDlgItemMessage(hDlg, IDC_LIST2, LB_ADDSTRING, 0, (LPARAM)texto);
         swprintf_s(texto, 80, L"IL Angulo(grados) = %.5f grados", (float)arg(SL.getIL())*180/M_PI);
         SendDlgItemMessage(hDlg, IDC_LIST2, LB_ADDSTRING, 0, (LPARAM)texto);
         swprintf_s(texto, 80, L"ILpu compleja = (%.5f + j %.5f) PU", (float)real(SL.getILpu()), (float)imag(SL.getILpu()));
         SendDlgItemMessage(hDlg, IDC_LIST2, LB_ADDSTRING, 0, (LPARAM)texto);
         swprintf_s(texto, 80, L"ILpu polar = (%.5f /__ %.5f) PU", (float)abs(SL.getILpu()), (float)arg(SL.getILpu()));
         SendDlgItemMessage(hDlg, IDC_LIST2, LB_ADDSTRING, 0, (LPARAM)texto);
         swprintf_s(texto, 80, L"ZL equiv (compleja) = (%.5f + j %.5f) Ohm", (float)real(SL.getZL()), (float)imag(SL.getZL()));
         SendDlgItemMessage(hDlg, IDC_LIST2, LB_ADDSTRING, 0, (LPARAM)texto);
         swprintf_s(texto, 80, L"ZL equiv (polar) = (%.5f /__ %.5f) Ohm, angulo en rad", (float)abs(SL.getZL()), (float)arg(SL.getZL()));
         SendDlgItemMessage(hDlg, IDC_LIST2, LB_ADDSTRING, 0, (LPARAM)texto);
         swprintf_s(texto, 80, L"ZL equiv (polar) = (%.5f /__ %.5f) Ohm, angulo en grados", (float)abs(SL.getZL()), (float)arg(SL.getZL())*180/M_PI);
         SendDlgItemMessage(hDlg, IDC_LIST2, LB_ADDSTRING, 0, (LPARAM)texto);
         swprintf_s(texto, 80, L"ZLpu equiv (compleja pu) = (%.5f + j %.5f) PU", (float)real(SL.getZLpu()), (float)imag(SL.getZLpu()));
         SendDlgItemMessage(hDlg, IDC_LIST2, LB_ADDSTRING, 0, (LPARAM)texto);
         swprintf_s(texto, 80, L"ZLpu equiv (polar pu) = (%.5f /__ %.5f) PU angulo en rad", (float)abs(SL.getZLpu()), (float)arg(SL.getZLpu()));
         SendDlgItemMessage(hDlg, IDC_LIST2, LB_ADDSTRING, 0, (LPARAM)texto);
         swprintf_s(texto, 80, L"ZLpu equiv (polar pu) = (%.5f /__ %.5f) PU angulo en grados", (float)abs(SL.getZLpu()), (float)arg(SL.getZLpu())*180/M_PI);
         SendDlgItemMessage(hDlg, IDC_LIST2, LB_ADDSTRING, 0, (LPARAM)texto);

     }
     return TRUE;
     case WM_COMMAND: {
         switch (LOWORD(wParam)) {
         case IDOK: {

             EndDialog(hDlg, FALSE);
         }
                  break;
         case IDCANCEL:
         {
             EndDialog(hDlg, FALSE);
         }
         break;
         }  //Fin del switch del COMMAND
     }
                    break;
     }  // Fin del switch del mensaje
     return FALSE;
 }

 BOOL CALLBACK DlgProc12(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
 {
     //Procedimiento para cargar el nombre de un proyecto existente

     static MatrixD* Datbas;
     switch (msg)                  /* manipulador del mensaje */
     {
     case WM_INITDIALOG:
         Datbas = (MatrixD*)lParam;
         SetDlgItemTextW(hDlg, IDC_EDIT1, L"MiProy");
         SetFocus(GetDlgItem(hDlg, IDC_EDIT1));
         return FALSE;
         break;

     case WM_COMMAND:
         switch (LOWORD(wParam)) {
         case IDOK: {
             GetDlgItemTextW(hDlg, IDC_EDIT1, (LPWSTR)Datbas->NombreProy, 80);
             EndDialog(hDlg, FALSE);
             break;
         }
         case IDCANCEL: {
             EndDialog(hDlg, FALSE);
             break;
         }
         }
         return TRUE;
     }
     return FALSE;
 }

 BOOL CALLBACK DlgProc13(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
 {
     //Procedimiento para cargar el nombre de un proyecto existente a ser editado

     static MatrixD* Datbas;
     switch (msg)                  /* manipulador del mensaje */
     {
     case WM_INITDIALOG:
         Datbas = (MatrixD*)lParam;
         SetDlgItemTextW(hDlg, IDC_EDIT1, L"MiProy");
         SetDlgItemTextW(hDlg, IDC_EDIT12, L"MiProyEditar");
         SetFocus(GetDlgItem(hDlg, IDC_EDIT12));
         return FALSE;
         break;

     case WM_COMMAND:
         switch (LOWORD(wParam)) {
         case IDOK: {
             GetDlgItemTextW(hDlg, IDC_EDIT1, (LPWSTR)Datbas->NombreProy, 80);
             GetDlgItemTextW(hDlg, IDC_EDIT12, (LPWSTR)Datbas->NombreProyE, 80);
             EndDialog(hDlg, FALSE);
             break;
         }
         case IDCANCEL: {
             EndDialog(hDlg, FALSE);
             break;
         }
         }
         return TRUE;
     }
     return FALSE;
 }

 BOOL CALLBACK DlgProc14(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
 {
     //Procedimiento para cargar los datos a editar en el proyecto

     static MatrixD* Datbas;
     wchar_t texto1[160] = L"xx";
     int nge = 0, nte = 0, nle = 0, nme = 0, nce = 0; //Elementos a eliminar
     int nga = 0, nta = 0, nla = 0, nma = 0, nca = 0; //Elementos a agregar
     
     switch (msg)                  /* manipulador del mensaje */
     {
     case WM_INITDIALOG:
         Datbas = (MatrixD*)lParam;
         Datbas->Eliminar.resize(5, std::vector<int>(10, { 0 })); //Inicializa vector de elementos a eliminar

         SetDlgItemTextW(hDlg, IDC_EDIT1, (LPCWSTR)Datbas->NombreProy);
         SetDlgItemTextW(hDlg, IDC_EDIT12, (LPCWSTR)Datbas->NombreProyE);

         swprintf_s(texto1, 160, L"Numero de Generadores: %i    Num. de Transformadores: %i    Num. de Lineas: %i    Num. de Motores: %i    Num. de Cargas SL: %i \n",
             (int)Datbas->ng, (int)Datbas->nt, (int)Datbas->nl, (int)Datbas->nm, (int)Datbas->nc);
         SendDlgItemMessage(hDlg, IDC_LIST1, LB_ADDSTRING, 0, (LPARAM)texto1);
         
         swprintf_s(texto1, 160, L"   ***DATOS DE LOS GENERADORES DEL SISTEMA***");
         SendDlgItemMessage(hDlg, IDC_LIST1, LB_ADDSTRING, 0, (LPARAM)texto1);
         swprintf_s(texto1, 160, L"%-14ls %-14ls %-14ls %-14ls %-14ls    %-14ls %-14ls", L"Gen. Numero", L"S nominal", L"V nominal", L"Xd", L"Ra", L"S base", L"V base");
         SendDlgItemMessage(hDlg, IDC_LIST1, LB_ADDSTRING, 0, (LPARAM)texto1);
         for (int i = 0; i < Datbas->ng; i++) {
             swprintf_s(texto1, 160, L"        %i %-6ls %14.2f  %14.2f  %9.5f  %9.5f  %14.2f  %14.2f",
                 (int)(i + 1), L"", (float)Datbas->Gen[i][0], (float)Datbas->Gen[i][1],
                 (float)Datbas->Gen[i][2],  (float)Datbas->Gen[i][3],
                 (float)Datbas->Gen[i][4], (float)Datbas->Gen[i][5]);
             SendDlgItemMessage(hDlg, IDC_LIST1, LB_ADDSTRING, 0, (LPARAM)texto1);
         }
         
         swprintf_s(texto1, 160, L"   ***DATOS DE LOS TRANSFORMADORES DEL SISTEMA***");
         SendDlgItemMessage(hDlg, IDC_LIST1, LB_ADDSTRING, 0, (LPARAM)texto1);
         swprintf_s(texto1, 160, L"%-14ls %-14ls %-14ls %-14ls %-14ls %-14ls    %-14ls %-14ls %-14ls", L"Transf. Numero", L"S nominal", L"VA nominal", L"VB nominal", L"Xt", L"Rt", L"S base", L"VA base", L"VB base");
         SendDlgItemMessage(hDlg, IDC_LIST1, LB_ADDSTRING, 0, (LPARAM)texto1);
         for (int i = 0; i < Datbas->nt; i++) {
             swprintf_s(texto1, 160, L"          %i %-6ls %14.2f  %14.2f %14.2f      %9.5f  %9.5f  %14.2f %14.2f  %14.2f",
                 (int)(i + 1), L"", (float)Datbas->Transf[i][0], (float)Datbas->Transf[i][1], (float)Datbas->Transf[i][2],
                 (float)Datbas->Transf[i][3], (float)Datbas->Transf[i][4],
                 (float)Datbas->Transf[i][5], (float)Datbas->Transf[i][6], (float)Datbas->Transf[i][7]);
             SendDlgItemMessage(hDlg, IDC_LIST1, LB_ADDSTRING, 0, (LPARAM)texto1);
         }

         swprintf_s(texto1, 160, L"   ***DATOS DE LAS LINEAS DEL SISTEMA***");
         SendDlgItemMessage(hDlg, IDC_LIST1, LB_ADDSTRING, 0, (LPARAM)texto1);
         swprintf_s(texto1, 160, L"%-14ls %-14ls %-14ls    %-14ls  %-14ls", L"Lin. Numero", L"XL (Ohm)", L"RL (Ohm)", L"S base", L"V base");
         SendDlgItemMessage(hDlg, IDC_LIST1, LB_ADDSTRING, 0, (LPARAM)texto1);
         for (int i = 0; i < Datbas->nl; i++) {
             swprintf_s(texto1, 160, L"        %i %-8ls  %9.5f    %9.5f  %14.2f  %14.2f",
                 (int)(i + 1), L"", (float)Datbas->Lin[i][0], (float)Datbas->Lin[i][1],
                 (float)Datbas->Lin[i][2], (float)Datbas->Lin[i][3]);
             SendDlgItemMessage(hDlg, IDC_LIST1, LB_ADDSTRING, 0, (LPARAM)texto1);
         }

         swprintf_s(texto1, 160, L"   ***DATOS DE LOS MOTORES DEL SISTEMA***");
         SendDlgItemMessage(hDlg, IDC_LIST1, LB_ADDSTRING, 0, (LPARAM)texto1);
         swprintf_s(texto1, 160, L"%-14ls %-14ls %-14ls %-14ls %-14ls    %-14ls %-14ls", L"Gen. Numero", L"S nominal", L"V nominal", L"Xd", L"Ra", L"S base", L"V base");
         SendDlgItemMessage(hDlg, IDC_LIST1, LB_ADDSTRING, 0, (LPARAM)texto1);
         for (int i = 0; i < Datbas->nm; i++) {
             swprintf_s(texto1, 160, L"        %i %-6ls %14.2f  %14.2f     %9.5f  %9.5f  %14.2f  %14.2f",
                 (int)(i + 1), L"", (float)Datbas->Mot[i][0], (float)Datbas->Mot[i][1],
                 (float)Datbas->Mot[i][2], (float)Datbas->Mot[i][3],
                 (float)Datbas->Mot[i][4], (float)Datbas->Mot[i][5]);
             SendDlgItemMessage(hDlg, IDC_LIST1, LB_ADDSTRING, 0, (LPARAM)texto1);
         }

         swprintf_s(texto1, 160, L"   ***DATOS DE LAS CARGAS DEL SISTEMA***");
         SendDlgItemMessage(hDlg, IDC_LIST1, LB_ADDSTRING, 0, (LPARAM)texto1);
         swprintf_s(texto1, 160, L"%-14ls %-14ls %-14ls %-14ls %-14ls %-14ls", L"Carga Numero", L"P (Mw)", L"Q (MVAR)", L"V nominal", L"S base", L"V base");
         SendDlgItemMessage(hDlg, IDC_LIST1, LB_ADDSTRING, 0, (LPARAM)texto1);
         for (int i = 0; i < Datbas->nc; i++) {
             swprintf_s(texto1, 160, L"        %i %-6ls %14.2f  %14.2f    %14.2f  %14.2f  %14.2f",
                 (int)(i + 1), L"", (float)Datbas->Car[i][0], (float)Datbas->Car[i][1],
                 (float)Datbas->Car[i][2], (float)Datbas->Car[i][3], (float)Datbas->Car[i][4]);
             SendDlgItemMessage(hDlg, IDC_LIST1, LB_ADDSTRING, 0, (LPARAM)texto1);
         }

         SetDlgItemInt(hDlg, IDC_EDIT2, nga, true); //No. de generadores a agregar
         SetDlgItemInt(hDlg, IDC_EDIT3, nta, true); //No. de transformadores a agregar
         SetDlgItemInt(hDlg, IDC_EDIT4, nla, true); //No. de lineas a agregar
         SetDlgItemInt(hDlg, IDC_EDIT5, nma, true); //No. de motores a agregar
         SetDlgItemInt(hDlg, IDC_EDIT6, nca, true); //No. de cargas a agregar

         SetDlgItemInt(hDlg, IDC_EDIT7, nge, true); //No. de generadores a eliminar
         SetDlgItemInt(hDlg, IDC_EDIT8, nte, true); //No. de transformadores a eliminar
         SetDlgItemInt(hDlg, IDC_EDIT9, nle, true); //No. de lineas a eliminar
         SetDlgItemInt(hDlg, IDC_EDIT10, nme, true); //No. de motores a eliminar
         SetDlgItemInt(hDlg, IDC_EDIT11, nce, true); //No. de cargas a eliminar

         SetDlgItemTextW(hDlg, IDC_EDIT13, (LPCWSTR)L"x,x"); //Generadores a eliminar
         SetDlgItemTextW(hDlg, IDC_EDIT14, (LPCWSTR)L"x,x"); //Generadores a eliminar
         SetDlgItemTextW(hDlg, IDC_EDIT15, (LPCWSTR)L"x,x"); //Generadores a eliminar
         SetDlgItemTextW(hDlg, IDC_EDIT16, (LPCWSTR)L"x,x"); //Generadores a eliminar
         SetDlgItemTextW(hDlg, IDC_EDIT17, (LPCWSTR)L"x,x"); //Generadores a eliminar

         SetFocus(GetDlgItem(hDlg, IDC_EDIT12));
         return FALSE;
         break;

     case WM_COMMAND:
         switch (LOWORD(wParam)) {
         case IDOK: {
             
             wchar_t varaux[20] = L"";
             wchar_t resultado[10] = L"";
             wchar_t* contexto;
             GetDlgItemTextW(hDlg, IDC_EDIT13, (LPWSTR)varaux, 10); //Generadores a eliminar
             if (varaux != L"x,x") {
                 int j = 0;
                 wchar_t* resultado = wcstok_s(varaux, L",", &contexto);
                 while (resultado != NULL) {
                     Datbas->Eliminar[0][j] = _wtoi(resultado);
                     j++;
                     resultado = wcstok_s(NULL, L",", &contexto);
                 }
             }
             GetDlgItemTextW(hDlg, IDC_EDIT14, (LPWSTR)varaux, 10); //Transformadores a eliminar
             if (varaux != L"x,x") {
                 int j = 0;
                 wchar_t* resultado = wcstok_s(varaux, L",", &contexto);
                 while (resultado != NULL) {
                     Datbas->Eliminar[1][j] = _wtoi(resultado);
                     j++;
                     resultado = wcstok_s(NULL, L",", &contexto);
                 }
             }
             GetDlgItemTextW(hDlg, IDC_EDIT15, (LPWSTR)varaux, 10); //Lineas a eliminar
             if (varaux != L"x,x") {
                 int j = 0;
                 wchar_t* resultado = wcstok_s(varaux, L",", &contexto);
                 while (resultado != NULL) {
                     Datbas->Eliminar[2][j] = _wtoi(resultado);
                     j++;
                     resultado = wcstok_s(NULL, L",", &contexto);
                 }
             }
             GetDlgItemTextW(hDlg, IDC_EDIT16, (LPWSTR)varaux, 10); //Motores a eliminar
             if (varaux != L"x,x") {
                 int j = 0;
                 wchar_t* resultado = wcstok_s(varaux, L",", &contexto);
                 while (resultado != NULL) {
                     Datbas->Eliminar[3][j] = _wtoi(resultado);
                     j++;
                     resultado = wcstok_s(NULL, L",", &contexto);
                 }
             }
             GetDlgItemTextW(hDlg, IDC_EDIT17, (LPWSTR)varaux, 10); //Cargas a eliminar
             if (varaux != L"x,x") {
                 int j = 0;
                 wchar_t* resultado = wcstok_s(varaux, L",", &contexto);
                 while (resultado != NULL) {
                     Datbas->Eliminar[4][j] = _wtoi(resultado);
                     j++;
                     resultado = wcstok_s(NULL, L",", &contexto);
                 }
             }

             BOOL Bnum = false;
             //Captura de los datos a agregar del nuevo proyecto EITADO;
             nga = (int)GetDlgItemInt(hDlg, IDC_EDIT2, &Bnum, TRUE);
             nta = (int)GetDlgItemInt(hDlg, IDC_EDIT3, &Bnum, TRUE);
             nla = (int)GetDlgItemInt(hDlg, IDC_EDIT4, &Bnum, TRUE);
             nma = (int)GetDlgItemInt(hDlg, IDC_EDIT5, &Bnum, TRUE);
             nca = (int)GetDlgItemInt(hDlg, IDC_EDIT6, &Bnum, TRUE);
            
             //Captura de los datos a eliminar del nuevo proyecto EITADO;
             nge = (int)GetDlgItemInt(hDlg, IDC_EDIT7, &Bnum, TRUE);
             nte = (int)GetDlgItemInt(hDlg, IDC_EDIT8, &Bnum, TRUE);
             nle = (int)GetDlgItemInt(hDlg, IDC_EDIT9, &Bnum, TRUE);
             nme = (int)GetDlgItemInt(hDlg, IDC_EDIT10, &Bnum, TRUE);
             nce = (int)GetDlgItemInt(hDlg, IDC_EDIT11, &Bnum, TRUE);

             //Se ajusta la candidad de equipos en el nuevo proyecto editado
             //Se agregan o se eliminan
             //Si Datbas->nxE = 0, la cantidad permanece igual. 
             if ((nga != 0) || (nge != 0)) { //Generadores
                 if (nga != 0) Datbas->ngE = Datbas->ng + nga;
                 if (nge != 0) Datbas->ngE = Datbas->ng - nge;
             }
             else Datbas->ngE = Datbas->ng;
             
             if ((nta != 0) || (nte != 0)) { //Transformadores
                 if (nta != 0) Datbas->ntE = Datbas->nt + nta;
                 if (nte != 0) Datbas->ntE = Datbas->nt - nte;
             }
             else Datbas->ntE = Datbas->nt;

             if ((nla != 0) || (nle != 0)) { //Lineas
                 if (nla != 0) Datbas->nlE = Datbas->nl + nla;
                 if (nle != 0) Datbas->nlE = Datbas->nl - nle;
             }
             else Datbas->nlE = Datbas->nl;

             if ((nma != 0) || (nme != 0)) { //Motores
                 if (nma != 0) Datbas->nmE = Datbas->nm + nma;
                 if (nme != 0) Datbas->nmE = Datbas->nm - nme;
             }
             else Datbas->nmE = Datbas->nm;

             if ((nca != 0) || (nce != 0)) { //Cargas SL
                 if (nca != 0) Datbas->ncE = Datbas->nc + nca;
                 if (nce != 0) Datbas->ncE = Datbas->nc - nce;
             }
             else Datbas->ncE = Datbas->nc;
             
             /*
             swprintf_s(texto1, 160, L"Dentro del windowproced valore de nuevo proy %i   %i  %i  %i  %i", (int)Datbas->ngE, (int)Datbas->ntE, 
                 (int)Datbas->nlE, (int)Datbas->nmE, (int)Datbas->ncE);
             MessageBoxW(hDlg, (LPCWSTR)texto1, L"INFORMACION", MB_ICONEXCLAMATION | MB_OK);
             
             swprintf_s(texto1, 160, L"Dentro del windowproced  a eliminar %i   %i  %i  %i", (int)Datbas->Eliminar[4][0], (int)Datbas->Eliminar[4][1],
                 (int)Datbas->Eliminar[4][2], (int)Datbas->Eliminar[4][3], (int)Datbas->Eliminar[4][4]);
             MessageBoxW(hDlg, (LPCWSTR)texto1, L"INFORMACION", MB_ICONEXCLAMATION | MB_OK);
             */

             EndDialog(hDlg, FALSE);
             break;
         }
         case IDCANCEL: {
             EndDialog(hDlg, FALSE);
             break;
         }
         }
         return TRUE;
     }
     return FALSE;
 }

 void LeerDatosProyecto(MatrixD* dat) {
     static MatrixD* DatosBase;
     DatosBase = (MatrixD*)dat;

     int ng, nt, nl, nm, nc;
     //double Mbase, Vvolt;
     fstream arch;
     arch.open(DatosBase->NombreProy);
     //arch.open(dat->NombreProy);
     int ind = 0;
     if (!arch) {
         cerr << "Error al abrir el archivo de datos del sistema.txt. " << endl;
         MessageBoxW(NULL, L"El archivo no existe", L"Error", IDOK);
         arch.close();
         return;
     }
     else {
         ind = 1;
     }

     arch >> DatosBase->ng >> DatosBase->nt >> DatosBase->nl >> DatosBase->nm >> DatosBase->nc;

     ng = (int)DatosBase->ng;	//Numero de generadores del sistema
     nt = (int)DatosBase->nt;	//Numero de transformadores del sistema
     nl = (int)DatosBase->nl;	//Numero de lineas del sistema
     nm = (int)DatosBase->nm;	//Numero de motores del sistema
     nc = (int)DatosBase->nc;	//Numero de cargas del sistema

     //Culmina la lectura de los primeros datos (datos b�sicos)
    
     dat->Gen.resize(ng, std::vector<double>(20, { 0.0 }));
     for (int i = 0; i < ng; i++) {
         for (int j = 0; j < 20; j++) {
             arch >> DatosBase->Gen[i][j];
         }
     }
     //Culmina la lectura de los datos de los generadores del sistema
     
     dat->Transf.resize(nt, std::vector<double>(20, { 0.0 }));
     for (int i = 0; i < nt; i++) {
         for (int j = 0; j < 20; j++) {
             arch >> DatosBase->Transf[i][j];
         }
     }
     //Culmina la lectura de los datos de los transformadores del sistema
     
     dat->Lin.resize(nl, std::vector<double>(20, { 0.0 }));
     for (int i = 0; i < nl; i++) {
         for (int j = 0; j < 20; j++) {
             arch >> DatosBase->Lin[i][j];
         }
     }
     //Culmina la lectura de los datos de las lineas del sistema

     dat->Mot.resize(nm, std::vector<double>(20, { 0.0 }));
     for (int i = 0; i < nm; i++) {
         for (int j = 0; j < 20; j++) {
             arch >> DatosBase->Mot[i][j];
         }
     }
     //Culmina la lectura de los datos de los motores del sistema
     
     dat->Car.resize(nc, std::vector<double>(20, { 0.0 }));
     for (int i = 0; i < nc; i++) {
         for (int j = 0; j < 20; j++) {
             arch >> DatosBase->Car[i][j];
         }
     }
     //Culmina la lectura de los datos de las cargas del sistema

     arch.close();
     return;
 }

 void CrearProyectoEditar(MatrixD* dat, MatrixD* datE) {
     wchar_t texto1[160] = L"";
     
     swprintf_s(datE->NombreProy, 80, dat->NombreProyE, 0L); //Se asigna al nomBre del proyecto editado
     //Garga e inicialización de datos del proyecto editado.
     
     datE->ng = dat->ngE;
     datE->nt = dat->ntE;
     datE->nl = dat->nlE;
     datE->nm = dat->nmE;
     datE->nc = dat->ncE;

     datE->Gen.resize(datE->ng, std::vector<double>(20, { 0.0 })); //Inicializa vector de Generadores
     datE->Transf.resize(datE->nt, std::vector<double>(20, { 0.0 })); //Inicializa vector de Transformadores
     datE->Lin.resize(datE->nl, std::vector<double>(20, { 0.0 })); //Inicializa vector de Lineas
     datE->Mot.resize(datE->nm, std::vector<double>(20, { 0.0 })); //Inicializa vector de Motores
     datE->Car.resize(datE->nc, std::vector<double>(20, { 0.0 })); //Inicializa vector de Cargas
     datE->Eliminar.resize(5, std::vector<int>(10, { 0 })); //Inicializa vector de elementos a eliminar

     
     for (int i = 0; i < 5; i++) {
         for (int j = 0; j < 10; j++) {
             datE->Eliminar[i][j] = dat->Eliminar[i][j];
         }
     }
     
     //************   GENERADORES
     if (dat->ngE >= dat->ng) { //Para el caso de que haya que agregar o dejar igual la cantidad de generadores
         for (int i = 0; i < dat->ng; i++) {
             for (int j = 0; j < 20; j++) {
                     datE->Gen[i][j] = dat->Gen[i][j];
             }
         }
     }
     else {  // Para el caso de que haya que eliminar generadores
         int iElm = 0;
         while (dat->Eliminar[0][iElm] != 0) {  //Se marcan los generadores a eliminar en dat->Gen[i][19].
             for (int i = 0; i < dat->ng; i++) {
                 if (dat->Eliminar[0][iElm] == i + 1) {
                     dat->Gen[i][19] = 1;
                 }
             }
             iElm++;
         }
         int k = 0;
         for (int i = 0; i < dat->ng; i++) {//Se copia en la base datE los generadores no eliminados
            if (dat->Gen[i][19] == 0) {
                for(int j = 0; j < 20; j++) {
                    datE->Gen[k][j] = dat->Gen[i][j];
                }
                k++;
            }
         }
     }

     //************   TRANSFORMADORES
     if (dat->ntE >= dat->nt) { //Para el caso de que haya que agregar o dejar igual la cantidad de transformadores
         for (int i = 0; i < dat->nt; i++) {
             for (int j = 0; j < 20; j++) {
                 datE->Transf[i][j] = dat->Transf[i][j];
             }
         }
     }
     else {  // Para el caso de que haya que eliminar transformadores
         int iElm = 0;
         while (dat->Eliminar[1][iElm] != 0) {  //Se marcan los transformadores a eliminar en dat->Transf[i][19].
             for (int i = 0; i < dat->nt; i++) {
                 if (dat->Eliminar[1][iElm] == i + 1) {
                     dat->Transf[i][19] = 1;
                 }
             }
             iElm++;
         }
         int k = 0;
         for (int i = 0; i < dat->nt; i++) {//Se copia en la base datE los transformadores no eliminados
             if (dat->Transf[i][19] == 0) {
                 for (int j = 0; j < 20; j++) {
                     datE->Transf[k][j] = dat->Transf[i][j];
                 }
                 k++;
             }
         }
     }

     //************   LINEAS
     if (dat->nlE >= dat->nl) { //Para el caso de que haya que agregar o dejar igual la cantidad de lineas
         for (int i = 0; i < dat->nl; i++) {
             for (int j = 0; j < 20; j++) {
                 datE->Lin[i][j] = dat->Lin[i][j];
             }
         }
     }
     else {  // Para el caso de que haya que eliminar lineas
         int iElm = 0;
         while (dat->Eliminar[2][iElm] != 0) {  //Se marcan las lineas a eliminar en dat->Lin[i][19].
             for (int i = 0; i < dat->nl; i++) {
                 if (dat->Eliminar[2][iElm] == i + 1) {
                     dat->Lin[i][19] = 1;
                 }
             }
             iElm++;
         }
         int k = 0;
         for (int i = 0; i < dat->nl; i++) {//Se copia en la base datE las lineas no eliminadas
             if (dat->Lin[i][19] == 0) {
                 for (int j = 0; j < 20; j++) {
                     datE->Lin[k][j] = dat->Lin[i][j];
                 }
                 k++;
             }
         }
     }

     //************   MOTORES
     if (dat->nmE >= dat->nm) { //Para el caso de que haya que agregar o dejar igual la cantidad de motores
         for (int i = 0; i < dat->nm; i++) {
             for (int j = 0; j < 20; j++) {
                 datE->Mot[i][j] = dat->Mot[i][j];
             }
         }
     }
     else {  // Para el caso de que haya que eliminar motores
         int iElm = 0;
         while (dat->Eliminar[3][iElm] != 0) {  //Se marcan los motores a eliminar en dat->Mot[i][19].
             for (int i = 0; i < dat->nm; i++) {
                 if (dat->Eliminar[3][iElm] == i + 1) {
                     dat->Mot[i][19] = 1;
                 }
             }
             iElm++;
         }
         int k = 0;
         for (int i = 0; i < dat->nm; i++) {//Se copia en la base datE los motores no eliminados
             if (dat->Mot[i][19] == 0) {
                 for (int j = 0; j < 20; j++) {
                     datE->Mot[k][j] = dat->Mot[i][j];
                 }
                 k++;
             }
         }
     }

     //************   CARGAS
     if (dat->ncE >= dat->nc) { //Para el caso de que haya que agregar o dejar igual la cantidad de cargas
         for (int i = 0; i < dat->nc; i++) {
             for (int j = 0; j < 20; j++) {
                 datE->Car[i][j] = dat->Car[i][j];
             }
         }
     }
     else {  // Para el caso de que haya que eliminar cargas
         int iElm = 0;
         while (dat->Eliminar[4][iElm] != 0) {  //Se marcan los cargas a eliminar en dat->Car[i][19].
             for (int i = 0; i < dat->nc; i++) {
                 if (dat->Eliminar[4][iElm] == i + 1) {
                     dat->Car[i][19] = 1;
                 }
             }
             iElm++;
         }
         int k = 0;
         for (int i = 0; i < dat->nc; i++) {//Se copia en la base datE los motores no eliminados
             if (dat->Car[i][19] == 0) {
                 for (int j = 0; j < 20; j++) {
                     datE->Car[k][j] = dat->Car[i][j];
                 }
                 k++;
             }
         }
     }
     /*
     for (int i = 0; i < datE->ng; i++) {
         swprintf_s(texto1, 160, L"valores del generador %i en datE->  %.2f   %.2f",
             i+1, (float)datE->Gen[i][0], (float)datE->Gen[i][1]);
         MessageBoxW(NULL, (LPCWSTR)texto1, L"dentro del procedimiento", MB_ICONEXCLAMATION | MB_OK);
     }
     
     for (int i = 0; i < datE->nt; i++) {
         swprintf_s(texto1, 160, L"valores del transformador %i en datE->  %.2f   %.2f",
             i+1, (float)datE->Transf[i][0], (float)datE->Transf[i][1]);
         MessageBoxW(NULL, (LPCWSTR)texto1, L"dentro del procedimiento", MB_ICONEXCLAMATION | MB_OK);
     }
     
     for (int i = 0; i < datE->nl; i++) {
         swprintf_s(texto1, 160, L"valores de linea %i en datE->  %.2f   %.2f",
             i + 1, (float)datE->Lin[i][0], (float)datE->Lin[i][1]);
         MessageBoxW(NULL, (LPCWSTR)texto1, L"dentro del procedimiento", MB_ICONEXCLAMATION | MB_OK);
     }

     for (int i = 0; i < datE->nm; i++) {
         swprintf_s(texto1, 160, L"valores de motor %i en datE->  %.2f   %.2f",
             i + 1, (float)datE->Mot[i][0], (float)datE->Mot[i][1]);
         MessageBoxW(NULL, (LPCWSTR)texto1, L"dentro del procedimiento", MB_ICONEXCLAMATION | MB_OK);
     }

     for (int i = 0; i < datE->nc; i++) {
         swprintf_s(texto1, 160, L"valores de carga %i en datE->  %.2f   %.2f",
             i + 1, (float)datE->Car[i][0], (float)datE->Car[i][1]);
         MessageBoxW(NULL, (LPCWSTR)texto1, L"dentro del procedimiento", MB_ICONEXCLAMATION | MB_OK);
     }
     */
 }

 BOOL CALLBACK ReportePantalla1(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam) {
     //Procedimiento para mostrar reporte en pantalla
     static MatrixD* Datbas;

     switch (msg) {                 // manipulador del mensaje
     case WM_INITDIALOG: {
         Datbas = (MatrixD*)lParam;
         wchar_t texto1[400], texto2[400];
         SetDlgItemTextW(hDlg, IDC_EDIT1, (LPCWSTR)Datbas->NombreProy);
         
         if (Datbas->ng != 0) {
             swprintf_s(texto1, 160, L"   ***DATOS DE LOS GENERADORES DEL SISTEMA***");
             SendDlgItemMessage(hDlg, IDC_LIST1, LB_ADDSTRING, 0, (LPARAM)texto1);
             swprintf_s(texto1, 200, L"%-14ls %-14ls %-14ls %-14ls %-14ls %-14ls %-18ls %-14ls %-14ls", L"Gen. Numero", L"Snom.MVA", L"Vnom.Kv", L"Xd PU", L"Ra PU", L"Inom.KA", L"ZbaseEquipo.Ohm", L"Xd.Ohm", L"Ra.Ohm");
             SendDlgItemMessage(hDlg, IDC_LIST1, LB_ADDSTRING, 0, (LPARAM)texto1);
             swprintf_s(texto2, 160, L"   ***RESULTADOS DE ANALISIS DE LOS GENERADORES DEL SISTEMA EN LA NUEVA BASE***");
             SendDlgItemMessage(hDlg, IDC_LIST2, LB_ADDSTRING, 0, (LPARAM)texto2);
             swprintf_s(texto2, 200, L"%-14ls %-14ls %-14ls %-14ls %-14ls %-14ls %-14ls %-14ls %-14ls", L"Gen. Numero", L"Sbase.KVA", L"Vbase.Kv", L"Xdnueva PU", L"Ranueva PU", L"Ibase.Ka", L"Zbase.Ohm", L"Xd.Ohm", L"Ra.Ohm");
             SendDlgItemMessage(hDlg, IDC_LIST2, LB_ADDSTRING, 0, (LPARAM)texto2);
         }

         HWND hListBox1 = GetDlgItem(hDlg, IDC_LIST1);
         HWND hListBox2 = GetDlgItem(hDlg, IDC_LIST2);
         HDC hdc1 = GetDC(hListBox1);
         HDC hdc2 = GetDC(hListBox2);
         HFONT hFont1 = (HFONT)SendMessage(hListBox1, WM_GETFONT, 0, 0);
         HFONT hFont2 = (HFONT)SendMessage(hListBox2, WM_GETFONT, 0, 0);
         SelectObject(hdc1, hFont1);
         SelectObject(hdc2, hFont2);
         SIZE size1, size2;
         int maxWidth1 = 0, maxWidth2 = 0;
         
         for (int i = 0; i < Datbas->ng; i++) {
             Generador G(Datbas->Gen[i][0], Datbas->Gen[i][1], Datbas->Gen[i][2], Datbas->Gen[i][3]);
             G.setBaseNueva(Datbas->Gen[i][4], Datbas->Gen[i][5]);
             swprintf_s(texto1, 300, L"        %i %-14ls %-14.2f  %-14.2f  %-14.5f  %-14.5f  %-14.5f  %-14.5f         %-14.5f %-14.5f",
                 (int)(i + 1), L"", (float)Datbas->Gen[i][0], (float)Datbas->Gen[i][1],
                 (float)Datbas->Gen[i][2], (float)Datbas->Gen[i][3],
                 (float)G.getIn(), (float)G.getZb(),
                 (float)(G.getXd()*G.getZb()), (float)(G.getRa() * G.getZb()));
             SendDlgItemMessage(hDlg, IDC_LIST1, LB_ADDSTRING, 0, (LPARAM)texto1);
             // Medir el ancho del texto1
             GetTextExtentPoint32W(hdc1, texto1, (int)wcslen(texto1), &size1);
             if (size1.cx > maxWidth1) maxWidth1 = size1.cx;

             swprintf_s(texto2, 300, L"        %i %-14ls %-14.2f %-14.2f      %-14.5f   %-14.5f      %-14.5f %-14.5f    %-14.5f %-14.5f",
                  (int)(i + 1), L"", (float)G.getMVA(), (float)G.getVbN(),
                  (float)G.getXdN(), (float)G.getRaN(), (float)G.getIbN(), (float)G.getZbN(),
                  (float)(G.getXdN() * G.getZbN()), (float)(G.getRaN() * G.getZbN()));
             SendDlgItemMessage(hDlg, IDC_LIST2, LB_ADDSTRING, 0, (LPARAM)texto2);
             // Medir el ancho del texto2
             GetTextExtentPoint32W(hdc2, texto2, (int)wcslen(texto2), &size2);
             if (size2.cx > maxWidth2) maxWidth2 = size2.cx;
         }
         
         if (Datbas->nt != 0) {
             swprintf_s(texto1, 160, L"   ***DATOS DE LOS TRANSFORMADORES DEL SISTEMA***");
             SendDlgItemMessage(hDlg, IDC_LIST1, LB_ADDSTRING, 0, (LPARAM)texto1);
             swprintf_s(texto1, 300, L"%-14ls %-14ls %-14ls %-14ls %-14ls %-14ls    %-14ls %-14ls %-14ls %-14ls %-14ls %-14ls %-14ls %-14ls", L"Transf. Numero", L"Snom.MVA", L"VnomA.Kv", L"VnomB.Kv", L"Xt  PU", L"Rt  PU", L"InomA.Ka", L"InomB.Ka", L"ZbaseA.Ohm", L"ZbaseB.Ohm", L"XtA.Ohm", L"XtB.Ohm", L"RtA.Ohm", L"RtB.Ohm");
             SendDlgItemMessage(hDlg, IDC_LIST1, LB_ADDSTRING, 0, (LPARAM)texto1);
             swprintf_s(texto2, 160, L"   ***RESULTADOS DE ANALISIS DE LOS TRANSFORMADORES DEL SISTEMA EN LA NUEVA BASE***");
             SendDlgItemMessage(hDlg, IDC_LIST2, LB_ADDSTRING, 0, (LPARAM)texto2);
             swprintf_s(texto2, 300, L"%-14ls %-14ls %-14ls %-14ls %-14ls %-14ls %-14ls %-14ls %-14ls %-14ls %-14ls %-14ls %-14ls %-14ls", L"Transf.Numero", L"Sbase.KVA", L"VbaseA.Kv", L"VbaseB.Kv", L"XtN PU", L"RtN PU", L"IbaseA.Ka", L"IbaseB.Ka", L"ZbaseA.Ohm", L"ZbaseB.Ohm", L"XtA.Ohm", L"XtB.ohm", L"RtA.Ohm", L"RtB.Ohm");
             SendDlgItemMessage(hDlg, IDC_LIST2, LB_ADDSTRING, 0, (LPARAM)texto2);
         }
         for (int i = 0; i < Datbas->nt; i++) {
             Transformador T(Datbas->Transf[i][0], Datbas->Transf[i][1], Datbas->Transf[i][2], Datbas->Transf[i][3], Datbas->Transf[i][4]);
             T.setBaseNueva(Datbas->Transf[i][5], Datbas->Transf[i][6], Datbas->Transf[i][7]);
             swprintf_s(texto1, 300, L"          %i %-6ls  %14.2f      %14.2f %14.2f  %14.5f  %14.5f  %14.5f %14.5f      %14.5f  %14.5f  %14.5f  %14.5f %14.5f %14.5f",
                 (int)(i + 1), L"", (float)Datbas->Transf[i][0], (float)Datbas->Transf[i][1], (float)Datbas->Transf[i][2],
                 (float)Datbas->Transf[i][3], (float)Datbas->Transf[i][4],
                 (float)T.getInA(), (float)T.getInB(), (float)T.getZbA(), (float)T.getZbB(),
                 (float)T.getXt()*T.getZbA(), (float)T.getXt() * T.getZbB(),
                 (float)T.getRtA(), (float)T.getRtB());
             //(float)T.getRt()* T.getZbA(), (float)T.getRt()* T.getZbB());
             SendDlgItemMessage(hDlg, IDC_LIST1, LB_ADDSTRING, 0, (LPARAM)texto1);
             // Medir el ancho del texto1
             GetTextExtentPoint32W(hdc1, texto1, (int)wcslen(texto1), &size1);
             if (size1.cx > maxWidth1) maxWidth1 = size1.cx;

             swprintf_s(texto2, 300, L"        %i %-14ls %-14.2f    %-14.5f %-14.5f %-14.5f %-14.5f %-14.5f %-14.5f %-14.5f    %-14.5f %-14.5f %-14.5f %-14.5f %-14.5f", (int)(i+1), L"", 
                    (float)T.getMVAN(), (float)T.getVnAN(), (float)T.getVnBN(), (float)T.getXtN(), (float)T.getRtN(),
                    (float)T.getIbAN(), (float)T.getIbBN(), (float)T.getZbAN(), (float)T.getZbBN(),
                    (float)T.getXtAN(), (float)T.getXtBN(), (float)T.getRtAN(), (float)T.getRtBN());
             SendDlgItemMessage(hDlg, IDC_LIST2, LB_ADDSTRING, 0, (LPARAM)texto2);
             
             GetTextExtentPoint32W(hdc2, texto1, (int)wcslen(texto1), &size2);
             if (size2.cx > maxWidth2) maxWidth2 = size2.cx;
         }

         if(Datbas->nl != 0) {
             swprintf_s(texto1, 160, L"   ***DATOS DE LAS LINEAS DEL SISTEMA***");
             SendDlgItemMessage(hDlg, IDC_LIST1, LB_ADDSTRING, 0, (LPARAM)texto1);
             swprintf_s(texto1, 300, L"%-14ls %-14ls %-14ls", L"Linea. Numero", L"Xl  OHM", L"RL  OHM");
             SendDlgItemMessage(hDlg, IDC_LIST1, LB_ADDSTRING, 0, (LPARAM)texto1);
             swprintf_s(texto2, 160, L"   ***RESULTADOS DE ANALISIS DE LAS LINEAS DEL SISTEMA EN LA NUEVA BASE***");
             SendDlgItemMessage(hDlg, IDC_LIST2, LB_ADDSTRING, 0, (LPARAM)texto2);
             swprintf_s(texto2, 300, L"%-14ls %-14ls %-14ls %-14ls %-14ls %-14ls %-14ls", L"Linea.Numero", L"XL  PU", L"RL  PU", L"Sbase.KVA", L"Vbase.Kv", L"Ibase.Ka", L"ZbaseB.Ohm");
             SendDlgItemMessage(hDlg, IDC_LIST2, LB_ADDSTRING, 0, (LPARAM)texto2);
         }
         for (int i = 0; i < Datbas->nl; i++) {
             Linea L(Datbas->Lin[i][2], Datbas->Lin[i][3], Datbas->Lin[i][0], Datbas->Lin[i][1]);
             swprintf_s(texto1, 200, L"          %i %-6ls  %10.5f   %10.5f", (int)(i+1), L"",
                 (float)L.getXL(), (float)L.getRL());
             SendDlgItemMessage(hDlg, IDC_LIST1, LB_ADDSTRING, 0, (LPARAM)texto1);
             // Medir el ancho del texto1
             GetTextExtentPoint32W(hdc1, texto1, (int)wcslen(texto1), &size1);
             if (size1.cx > maxWidth1) maxWidth1 = size1.cx;


             swprintf_s(texto2, 300, L"        %i %-10ls %-14.5f %-14.5f %-14.2f %-14.2f    %-14.5f %-14.5f", (int)(i + 1), L"",
                 (float)L.getXpu(), (float)L.getRpu(), (float)L.getMVAb(), (float)L.getVb(),
                 (float)L.getIb(), (float)L.getZb());
             SendDlgItemMessage(hDlg, IDC_LIST2, LB_ADDSTRING, 0, (LPARAM)texto2);

             GetTextExtentPoint32W(hdc2, texto1, (int)wcslen(texto1), &size2);
             if (size2.cx > maxWidth2) maxWidth2 = size2.cx;

         }

         if(Datbas->nm != 0) {
             swprintf_s(texto1, 160, L"   ***DATOS DE LOS MOTORES DEL SISTEMA***");
             SendDlgItemMessage(hDlg, IDC_LIST1, LB_ADDSTRING, 0, (LPARAM)texto1);
             swprintf_s(texto1, 200, L"%-14ls %-14ls %-14ls %-14ls %-14ls %-14ls %-18ls %-14ls %-14ls", L"Mot. Numero", L"Snom.MVA", L"Vnom.Kv", L"Xd PU  ", L"Ra PU  ", L"Inom.KA", L"ZbaseEquipo.Ohm", L"Xd.Ohm", L"Ra.Ohm");
             SendDlgItemMessage(hDlg, IDC_LIST1, LB_ADDSTRING, 0, (LPARAM)texto1);
             swprintf_s(texto2, 160, L"   ***RESULTADOS DE ANALISIS DE LOS MOTORES DEL SISTEMA EN LA NUEVA BASE***");
             SendDlgItemMessage(hDlg, IDC_LIST2, LB_ADDSTRING, 0, (LPARAM)texto2);
             swprintf_s(texto2, 200, L"%-14ls %-14ls %-14ls %-14ls %-14ls %-14ls %-14ls %-14ls %-14ls", L"Mot. Numero", L"Sbase.KVA", L"Vbase.Kv", L"Xdnueva PU", L"Ranueva PU", L"Ibase.Ka", L"Zbase.Ohm", L"Xd.Ohm", L"Ra.Ohm");
             SendDlgItemMessage(hDlg, IDC_LIST2, LB_ADDSTRING, 0, (LPARAM)texto2);
         }
         for (int i = 0; i < Datbas->nm; i++) {
             Motor M(Datbas->Mot[i][0], Datbas->Mot[i][1], Datbas->Mot[i][2], Datbas->Mot[i][3]);
             M.setBaseNueva(Datbas->Mot[i][4], Datbas->Mot[i][5]);
             swprintf_s(texto1, 300, L"       %i %-14ls %-14.2f  %-14.2f   %-12.5f %12.5f      %-14.5f      %-14.5f        %-14.5f %-14.5f",
                 (int)(i + 1), L"", (float)Datbas->Mot[i][0], (float)Datbas->Mot[i][1],
                 (float)Datbas->Mot[i][2], (float)Datbas->Mot[i][3],
                 (float)M.getIn(), (float)M.getZb(),
                 (float)(M.getXd() * M.getZb()), (float)(M.getRa() * M.getZb()));
             SendDlgItemMessage(hDlg, IDC_LIST1, LB_ADDSTRING, 0, (LPARAM)texto1);
             // Medir el ancho del texto1
             GetTextExtentPoint32W(hdc1, texto1, (int)wcslen(texto1), &size1);
             if (size1.cx > maxWidth1) maxWidth1 = size1.cx;
             
             swprintf_s(texto2, 300, L"        %i %-14ls %-14.2f      %-14.2f   %-14.5f   %-14.5f      %-14.5f %-14.5f    %-14.5f %-14.5f",
                 (int)(i + 1), L"", (float)M.getMVAN(), (float)M.getVbN(),
                 (float)M.getXdN(), (float)M.getRaN(), (float)M.getIbN(), (float)M.getZbN(),
                 (float)(M.getXdN() * M.getZbN()), (float)(M.getRaN() * M.getZbN()));
             SendDlgItemMessage(hDlg, IDC_LIST2, LB_ADDSTRING, 0, (LPARAM)texto2);
             // Medir el ancho del texto2
             GetTextExtentPoint32W(hdc2, texto2, (int)wcslen(texto2), &size2);
             if (size2.cx > maxWidth2) maxWidth2 = size2.cx;
             
         }
         if(Datbas->nc != 0) {
             swprintf_s(texto1, 160, L"   ***DATOS DE LAS CARGAS DEL SISTEMA***");
             SendDlgItemMessage(hDlg, IDC_LIST1, LB_ADDSTRING, 0, (LPARAM)texto1);
             swprintf_s(texto1, 400, L"%-14ls %-14ls %-14ls %-14ls %-28ls %-42ls        %-28ls     %-42ls   %-14ls  %-14ls %-34ls %-28ls", L"Carga Numero", L"PL  MW", L"QL  MVAR", L"Vnom  Kv", L"Sn MVA (Forma Compleja)", L"Sn MVA (Forma Polar angulo en rad/grados)", L"In Ka(forma compleja)", L"In Ka(forma polar angulo en rad/grados)", L"FP COS(TETA)", L"Tipo de FP", L"Zeqv en Ohm (forma compleja)", L"Zeqv en Ohm (forma polar)");
             SendDlgItemMessage(hDlg, IDC_LIST1, LB_ADDSTRING, 0, (LPARAM)texto1);
             swprintf_s(texto2, 160, L"   ***RESULTADOS DE ANALISIS DE LAS CARGAS DEL SISTEMA EN LA NUEVA BASE***");
             SendDlgItemMessage(hDlg, IDC_LIST2, LB_ADDSTRING, 0, (LPARAM)texto2);
             swprintf_s(texto2, 400, L"%-14ls %-14ls %-14ls %-14ls %-14ls %-32ls %-48ls  %-34ls %-46ls  %-34ls %-42ls", L"Carga Numero", L"Sbase.MVA", L"Vbase.Kv", L"Ibase.Ka", L"Zbase.Ohm", L"SL en PU (forma compleja)", L"SL en PU (forma polar angulo en rad/grados)", L"IL PU (forma compleja)", L"IL PU (forma polar angulo en rad/grados)", L"Zeqv PU (forma compleja)", L"Zeqv PU (forma polar angulo en rad/grados)");
             SendDlgItemMessage(hDlg, IDC_LIST2, LB_ADDSTRING, 0, (LPARAM)texto2);
         }
         for (int i = 0; i < Datbas->nc; i++) {
             Carga SL(Datbas->Car[i][0], Datbas->Car[i][1], Datbas->Car[i][2], Datbas->Car[i][3], Datbas->Car[i][4]);
             swprintf_s(texto1, 400, L"          %i %-6ls  %14.2f %14.2f %14.2f    %14.5f + j%-14.5f  %14.5f /%-10.5frad/%-10.5fGrados %14.5f + j%-14.5f  %14.5f /%-10.5frad/%-10.5fGrados     %-14.5f %14ls  %14.5f + j%-14.5f  %14.5f /%-10.5frad/%-10.5fGrados", (int)(i + 1), L"",
                 (float)SL.getPL(), (float)SL.getQL(), (float)SL.getVLn(),
                 (float)real(SL.getSL()), (float)imag(SL.getSL()),
                 (float)SL.getMVASL(), (float)SL.getAngFP(), (float)SL.getAngFPGr(),
                 (float)real(SL.getIL()), (float)imag(SL.getIL()),
                 (float)abs(SL.getIL()), (float)arg(SL.getIL()), (float)arg(SL.getIL())*180/M_PI,
                 (float)SL.getFP(), (wchar_t*)SL.gettipoFP(),
                 (float)real(SL.getZL()), (float)imag(SL.getZL()),
                 (float)abs(SL.getZL()), (float)arg(SL.getZL()), (float)arg(SL.getZL())*180/M_PI);
             SendDlgItemMessage(hDlg, IDC_LIST1, LB_ADDSTRING, 0, (LPARAM)texto1);
             // Medir el ancho del texto1
             GetTextExtentPoint32W(hdc1, texto1, (int)wcslen(texto1), &size1);
             if (size1.cx > maxWidth1) maxWidth1 = size1.cx;

             
             swprintf_s(texto2, 400, L"        %i %-14ls   %-14.2f %-14.2f     %-14.5f %-14.5f  %14.5f + j%-14.5f  %14.5f /%-10.5frad/%-10.5fGrados  %14.5f + j%-14.5f  %14.5f /%-10.5frad/%-10.5fGrados  %14.5f + j%-14.5f  %14.5f /%-10.5frad/%-10.5fGrados", (int)(i + 1), L"",
                 (float)SL.getSbase(), (float)SL.getVbase(), (float)SL.getIbase(), (float)SL.getZbase(),
                 (float)real(SL.getSLpu()), (float)imag(SL.getSLpu()),
                 (float)abs(SL.getSLpu()), (float)arg(SL.getSLpu()), (float)arg(SL.getSLpu())*180/M_PI,
                 (float)real(SL.getILpu()), (float)imag(SL.getILpu()),
                 (float)abs(SL.getILpu()), (float)arg(SL.getILpu()), (float)arg(SL.getILpu()) * 180 / M_PI,
                 (float)real(SL.getZLpu()), (float)imag(SL.getZLpu()),
                 (float)abs(SL.getZLpu()), (float)arg(SL.getZLpu()), (float)arg(SL.getZLpu()) * 180 / M_PI);
             SendDlgItemMessage(hDlg, IDC_LIST2, LB_ADDSTRING, 0, (LPARAM)texto2);

             GetTextExtentPoint32W(hdc2, texto1, (int)wcslen(texto1), &size2);
             if (size2.cx > maxWidth2) maxWidth2 = size2.cx;
             
         }

         ReleaseDC(hListBox1, hdc1);
         // Establecer la extensión horizontal de texto1
         SendMessageW(hListBox1, LB_SETHORIZONTALEXTENT, (WPARAM)maxWidth1 + 10, 0);
         ReleaseDC(hListBox2, hdc2);
         // Establecer la extensión horizontal
         SendMessageW(hListBox2, LB_SETHORIZONTALEXTENT, (WPARAM)maxWidth2 + 10, 0);

     } //FINAL DE WM_INITDIALOG
     return TRUE;
     case WM_COMMAND: {
         switch (LOWORD(wParam)) {
         case IDOK: {
             EndDialog(hDlg, FALSE);
         }
         break;

         case IDCANCEL: {
             EndDialog(hDlg, FALSE);
         }
         break;
         }//Final del switch (LOWORD(wParam))
     }//Final del COMMAND
     break;
     case WM_KEYDOWN:
         if (wParam == VK_LEFT) {
             SendMessageW(GetDlgItem(hDlg, IDC_LIST1), WM_HSCROLL, SB_LINELEFT, 0);
         }
         else if (wParam == VK_RIGHT) {
             SendMessageW(GetDlgItem(hDlg, IDC_LIST1), WM_HSCROLL, SB_LINERIGHT, 0);
         }
         return TRUE;
     }//Final del switch msg
     return FALSE;
 }

 BOOL CALLBACK DialogoNombreReporte1(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
 {
     //Procedimiento para cargar el nombre del archivo de reporte1

     static MatrixD* Datbas;
     switch (msg)                  /* manipulador del mensaje */
     {
     case WM_INITDIALOG:
         Datbas = (MatrixD*)lParam;
         SetDlgItemTextW(hDlg, IDC_EDIT1, Datbas->NombreReporte1);
         SetFocus(GetDlgItem(hDlg, IDC_EDIT1));
         return FALSE;
         break;

     case WM_COMMAND:
         switch (LOWORD(wParam)) {
         case IDOK: {
             GetDlgItemTextW(hDlg, IDC_EDIT1, (LPWSTR)Datbas->NombreReporte1, 80);
             EndDialog(hDlg, FALSE);
             break;
         }
         case IDCANCEL: {
             EndDialog(hDlg, FALSE);
             break;
         }
         }
         return TRUE;
     }
     return FALSE;
 }

 void ReporteArchivo1(MatrixD* Dat) {
     wchar_t Texto[150] = L"";
     const wchar_t* Tex = Texto;
     swprintf(Texto, 150, Dat->NombreReporte1);
     wofstream archivo(Tex);  //constructor de ofstream
     archivo.imbue(std::locale(""));
     archivo << "Nombre del proyecto: " << Dat->NombreProy << endl;
     archivo << "Nombre del archivo que contiene el reporte: " << Dat->NombreReporte1 << endl;
     archivo << "------------------------------------------------------------------------------------------\n";

     archivo << "Datos Basicos del sistema" << endl;
     archivo << left << setw(25) << "Cantidad de Generadores" << setw(28) << "Cantidad de Transformadores" << setw(25) << "Cantidad de Lineas" << setw(25) << "Cantidad de Motores" << setw(25) << "Cantidad de Cargas SL" << endl;
     archivo << "         " << left << setw(25) << Dat->ng << setw(25) << Dat->nt << setw(25) << Dat->nl << setw(25) << Dat->nm << Dat->nc << endl;
     archivo << "------------------------------------------------------------------------------------------------------------------------------\n";

     if (Dat->ng != 0) {
        archivo << "Datos de los generadores del sistema:" << endl;
        archivo << left << setw(10) << "No. Gen" << setw(15) << "S nom (MVA)" << setw(15) << "V nom (Kv)" << setw(15) << "Xd en PU" << setw(15) <<
         "Ra en PU" << setw(15) << "Ibase equipo" << setw(15) << "Zbase equipo" << setw(15)<< "Xd en Ohm" << setw(15) << "Ra en Ohm" << endl;
     }
     for (int i = 0; i < Dat->ng; i++) {
         Generador G(Dat->Gen[i][0], Dat->Gen[i][1], Dat->Gen[i][2], Dat->Gen[i][3]);
         G.setBaseNueva(Dat->Gen[i][4], Dat->Gen[i][5]);
         
         archivo << fixed << setprecision(2) << right << setw(4) << i+1 << setw(13) << G.getMVA() << setw(15) << G.getVn() 
             << fixed << setprecision(5) << setw(15) << G.getXd() << setw(15) << G.getRa() << 
             setw(15) << G.getIn() << setw(15) << G.getZb() << setw(15) << G.getXd()*G.getZb() << setw(15) << G.getRa() * G.getZb() << endl;
     }

     if (Dat->ng != 0) {
         archivo << "Analisis de los generadores del sistema en base nueva:" << endl;
         archivo << left << setw(10) << "No. Gen" << setw(18) << "Sbase.Nueva.MVA" << setw(18) << "Vbase.Nueva.Kv" << setw(18) << "Xd.Nueva.PU" << setw(18) <<
             "Ra.Nueva.PU" << setw(18) << "Ibase.Nueva.Ka" << setw(18) << "Zbase.Nueva.Ohm" << setw(18) << "Xd.Nueva.Ohm" << setw(18) << "Ra.Nueva.Ohm" << endl;
     }
     for (int i = 0; i < Dat->ng; i++) {
         Generador G(Dat->Gen[i][0], Dat->Gen[i][1], Dat->Gen[i][2], Dat->Gen[i][3]);
         G.setBaseNueva(Dat->Gen[i][4], Dat->Gen[i][5]);

         archivo << fixed << setprecision(2) << right << setw(4) << i + 1 << setw(13) << G.getMVAN() << setw(18) << G.getVbN()
             << fixed << setprecision(5) << setw(18) << G.getXdN() << setw(18) << G.getRaN() <<
             setw(18) << G.getIbN() << setw(18) << G.getZbN() << setw(18) << G.getXdN() * G.getZbN() << setw(18) << G.getRaN() * G.getZbN() << endl;
     }

     archivo << "------------------------------------------------------------------------------------------------------------------------------\n";
     if (Dat->nt != 0) {
         archivo << "Datos de los transformadores del sistema:" << endl;
         archivo << left << setw(12) << "No. Transf" << setw(15) << "Snom.MVA" << setw(30) << "Vnom.Equipo.Kv Alta/Baja" << setw(34) << "Xt.Equipo en PU/AltaOhm/BajaOhm" << setw(30) << "Ibase.Equipo.Ka. Alta/Baja" << setw(30) << "Zbase.Equipo.Ohm Alta/Baja" << endl;
     }
     for (int i = 0; i < Dat->nt; i++) {
         Transformador T(Dat->Transf[i][0], Dat->Transf[i][1], Dat->Transf[i][2], Dat->Transf[i][3], Dat->Transf[i][4]);
         T.setBaseNueva(Dat->Transf[i][5], Dat->Transf[i][6], Dat->Transf[i][7]);
         archivo << fixed << setprecision(2) << right << setw(4) << i + 1 << setw(15) << T.getMVA() <<
                setw(20) << T.getVnA() << "/" << T.getVnB() <<  setprecision(5) <<
                setw(25) << T.getXt() << "/" << T.getXt() * T.getZbA() << "/" << T.getXt() * T.getZbB() <<
                setw(20) << T.getInA() << "/" << T.getInB() <<
                setw(20) << T.getZbA() << "/" << T.getZbB() << endl;
     }
     if (Dat->nt != 0) {
         archivo << "Analisis de los transformadores del sistema en base nueva:" << endl;
         archivo << left << setw(12) << "No. Transf" << setw(17) << "Sbase.Nueva.MVA" << setw(30) << "Vbase.Nueva.Kv Alta/Baja" << setw(34) << "Xt.Nueva en PU/AltaOhm/BajaOhm" << setw(30) << "Ibase.Nueva.Ka. Alta/Baja" << setw(30) << "Zbase.Nueva.Ohm Alta/Baja" << endl;
     }
     for (int i = 0; i < Dat->nt; i++) {
         Transformador T(Dat->Transf[i][0], Dat->Transf[i][1], Dat->Transf[i][2], Dat->Transf[i][3], Dat->Transf[i][4]);
         T.setBaseNueva(Dat->Transf[i][5], Dat->Transf[i][6], Dat->Transf[i][7]);
         archivo << fixed << setprecision(2) << right << setw(4) << i + 1 << setw(15) << T.getMVAN() <<
             setw(20) << T.getVnAN() << "/" << T.getVnBN() << setprecision(5) <<
             setw(25) << T.getXtN() << "/" << T.getXtN() * T.getZbAN() << "/" << T.getXtN() * T.getZbBN() <<
             setw(20) << T.getIbAN() << "/" << T.getIbBN() <<
             setw(20) << T.getZbAN() << "/" << T.getZbBN() << endl;
     }

     archivo << "------------------------------------------------------------------------------------------------------------------------------\n";
     if (Dat->nl != 0) {
         archivo << "Datos de las lineas del sistema:" << endl;
         archivo << left << setw(12) << "No. Linea" << setw(15) << "Xl en Ohm" << setw(15) << "RL en Ohm" << setw(15) << "Sbase en MVA" << setw(15) << "Vbase en Kv" << endl;
     }
     for (int i = 0; i < Dat->nl; i++) {
         Linea L(Dat->Lin[i][2], Dat->Lin[i][3], Dat->Lin[i][0], Dat->Lin[i][1]);
         archivo << fixed << setprecision(2) << right << setw(4) << i + 1 << setw(15) << L.getXL() <<
             setw(15) << L.getRL() << setw(15) << L.getMVAb() << setw(15) << L.getVb() << endl;
     }
     if (Dat->nl != 0) {
         archivo << "Analisis de las del sistema en base nueva:" << endl;
         archivo << left << setw(12) << "No. Linea" << setw(13) << "Sbase.MVA" << setw(13) << "Vbase.Kv" << setw(13) << "Ibase.Ka" << setw(13) << "Zbase.Ohm" << setw(13) << "XL en PU" << setw(13) << "RLen PU" <<
             setw(55) << "ZL en Ohm (forma binomica/forma polar)" << setw(40) << "ZL en PU (forma binomica/magnitud)" << endl;
     }
     for (int i = 0; i < Dat->nl; i++) {
         Linea L(Dat->Lin[i][2], Dat->Lin[i][3], Dat->Lin[i][0], Dat->Lin[i][1]);
         archivo << fixed << setprecision(2) << right << setw(4) << i + 1 << setw(13) << L.getMVAb() <<
             setw(13) << L.getVb() << setw(13) << setprecision(5) << L.getIb() << setw(15) << L.getZb() << 
             setw(13) << L.getXpu() << setw(13) << L.getRpu() <<
             setw(13) << real(L.getZL()) << " + j" <<imag(L.getZL()) << " / " << abs(L.getZL()) << "/" << arg(L.getZL()) << "rad/" << arg(L.getZL())*180/M_PI << "°" <<
             setw(13) << real(L.getZLpu()) << " + j" << imag(L.getZLpu()) << " / " << abs(L.getZLpu()) << endl;
     }

     archivo << "------------------------------------------------------------------------------------------------------------------------------\n";

     if (Dat->nm != 0) {
         archivo << "Datos de los motores del sistema:" << endl;
         archivo << left << setw(10) << "No. Mot" << setw(15) << "S nom (MVA)" << setw(15) << "V nom (Kv)" << setw(15) << "Xd en PU" << setw(15) <<
             "Ra en PU" << setw(15) << "Ibase equipo" << setw(15) << "Zbase equipo" << setw(15) << "Xd en Ohm" << setw(15) << "Ra en Ohm" << endl;
     }
     for (int i = 0; i < Dat->nm; i++) {
         Motor M(Dat->Mot[i][0], Dat->Mot[i][1], Dat->Mot[i][2], Dat->Mot[i][3]);
         M.setBaseNueva(Dat->Mot[i][4], Dat->Mot[i][5]);

         archivo << fixed << setprecision(2) << right << setw(4) << i + 1 << setw(13) << M.getMVA() << setw(15) << M.getVn()
             << fixed << setprecision(5) << setw(15) << M.getXd() << setw(15) << M.getRa() <<
             setw(15) << M.getIn() << setw(15) << M.getZb() << setw(15) << M.getXd() * M.getZb() << setw(15) << M.getRa() * M.getZb() << endl;
     }
     if (Dat->nm != 0) {
         archivo << "Analisis de los motores del sistema en base nueva:" << endl;
         archivo << left << setw(10) << "No. Mot" << setw(18) << "Sbase.Nueva.MVA" << setw(18) << "Vbase.Nueva.Kv" << setw(18) << "Xd.Nueva.PU" << setw(18) <<
             "Ra.Nueva.PU" << setw(18) << "Ibase.Nueva.Ka" << setw(18) << "Zbase.Nueva.Ohm" << setw(18) << "Xd.Nueva.Ohm" << setw(18) << "Ra.Nueva.Ohm" << endl;
     }
     for (int i = 0; i < Dat->nm; i++) {
         Motor M(Dat->Mot[i][0], Dat->Mot[i][1], Dat->Mot[i][2], Dat->Mot[i][3]);
         M.setBaseNueva(Dat->Mot[i][4], Dat->Mot[i][5]);

         archivo << fixed << setprecision(2) << right << setw(4) << i + 1 << setw(13) << M.getMVAN() << setw(18) << M.getVbN()
             << fixed << setprecision(5) << setw(18) << M.getXdN() << setw(18) << M.getRaN() <<
             setw(18) << M.getIbN() << setw(18) << M.getZbN() << setw(18) << M.getXdN() * M.getZbN() << setw(18) << M.getRaN() * M.getZbN() << endl;
     }


     archivo << "------------------------------------------------------------------------------------------------------------------------------\n";
     if (Dat->nc != 0) {
         archivo << "Datos de las cargas del sistema:" << endl;
         archivo << left << setw(10) << "No.Carga" << setw(15) << "PL en MW" << setw(15) << "QL en MVAR" << setw(20) <<
             "VLnominal Kv/PU" << setw(15) << "FP (cos(teta))" << setw(15) << "Tipo FP" <<
             setw(50) << "SL en MVA forma compleja/forma polar" << endl;
     }
     for (int i = 0; i < Dat->nc; i++) {
         Carga SL(Dat->Car[i][0], Dat->Car[i][1], Dat->Car[i][2], Dat->Car[i][3], Dat->Car[i][4]);
         archivo << fixed << setprecision(2) << right << setw(4) << i + 1 << setw(12) << SL.getPL() <<
             setw(15) << SL.getQL() << setw(15) << SL.getVLn() << " /" << setprecision(5) << SL.getVLnpu() <<
             setw(15) << SL.getFP() << setw(12) << SL.gettipoFP() <<
             setw(15) << SL.getPL() << "+ j" << SL.getQL() << " /" << SL.getMVASL() << " /" << SL.getAngFP() << "rad/" << SL.getAngFPGr() << "°" << endl;
     }
     if (Dat->nc != 0) {
         archivo << "Analisis de las cargas del sistema en base nueva:" << endl;
         archivo << left << setw(10) << "No.Carga" << setw(13) << "Sbase.MVA" << setw(13) << "Vbase.Kv" << setw(13) << "Ibase.Ka" << setw(13) << "Zbase.Ohm" <<
             setw(54) << "IL.Ka forma binomica/forma polar" <<
             setw(40) << "IL.PU forma binomica/forma polar" << endl;
     }
     for (int i = 0; i < Dat->nc; i++) {
         Carga SL(Dat->Car[i][0], Dat->Car[i][1], Dat->Car[i][2], Dat->Car[i][3], Dat->Car[i][4]);
         
         archivo << fixed << setprecision(2) << right << setw(4) << i + 1 <<
             setw(13) << SL.getSbase() << setw(13) << SL.getVbase() << setw(13) << setprecision(5) << SL.getIbase() << setw(13) << SL.getZbase() <<
             setw(13) << real(SL.getIL()) << "+ j" << imag(SL.getIL()) << " /" << abs(SL.getIL()) << "/" << arg(SL.getIL()) << "rad/"  << arg(SL.getIL())*180/M_PI << "°" << 
             setw(13) << real(SL.getILpu()) << "+ j" << imag(SL.getILpu()) << " /" << abs(SL.getILpu()) << "/" << arg(SL.getILpu()) << "rad/" << arg(SL.getILpu()) * 180 / M_PI << "°" << endl;
     }
     if (Dat->nc != 0) {
         archivo << "Impedancias equivalentes de la carga:" << endl;
         archivo << left << setw(10) << "No.Carga" <<
             setw(54) << "ZL.Ohm forma binomica/forma polar" <<
             setw(40) << "ZL.PU forma binomica/forma polar" << endl;
     }
     for (int i = 0; i < Dat->nc; i++) {
         Carga SL(Dat->Car[i][0], Dat->Car[i][1], Dat->Car[i][2], Dat->Car[i][3], Dat->Car[i][4]);

         archivo << fixed << setprecision(5) << right << setw(4) << i + 1 << 
             setw(13) << real(SL.getZL()) << "+ j" << imag(SL.getZL()) << " /" << abs(SL.getZL()) << "/" << arg(SL.getZL()) << "rad/" << arg(SL.getZL()) * 180 / M_PI << "°" <<
             setw(13) << real(SL.getZLpu()) << "+ j" << imag(SL.getZLpu()) << " /" << abs(SL.getZLpu()) << "/" << arg(SL.getZLpu()) << "rad/" << arg(SL.getZLpu()) * 180 / M_PI << "°" << endl;
     }

     archivo << "------------------------------------------------------------------------------------------------------------------------------\n";

     archivo.close();
 }

 void DibujarDiagramaVectorial(MatrixD* dat) {
     sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "Diagrama Fasorial Encadenado - SFML 3.1");
     window.setFramerateLimit(60);

     // --- Cargar Fuente del Sistema ---
     sf::Font fuente;
     // Intentamos cargar la fuente Arial de Windows. Si usas Linux o Mac, aseg�rate de colocar el archivo arial.ttf en la carpeta del proyecto.
     if (!fuente.openFromFile("C:\\Windows\\Fonts\\arial.ttf")) {
         if (!fuente.openFromFile("arial.ttf")) {
             MessageBoxW(NULL, L"No se pudo cargar la fuente arial.ttf", L"ERROR", MB_ICONEXCLAMATION | MB_OK);
             //std::cout << "Error: No se pudo cargar la fuente arial.ttf. Las etiquetas no se mostraran." << std::endl;
         }
     }

     std::vector<VectorGrafico> misVectores;
     sf::Vector2f centroVentana(400.f, 300.f);

     // --- Creaci�n del Eje Cartesiano de Fondo ---
     sf::VertexArray ejes(sf::PrimitiveType::Lines, 4);
     sf::Color colorEje(60, 60, 60);

     ejes[0].position = sf::Vector2f(0.f, centroVentana.y);
     ejes[0].color = colorEje;
     ejes[1].position = sf::Vector2f(800.f, centroVentana.y);
     ejes[1].color = colorEje;

     ejes[2].position = sf::Vector2f(centroVentana.x, 0.f);
     ejes[2].color = colorEje;
     ejes[3].position = sf::Vector2f(centroVentana.x, 600.f);
     ejes[3].color = colorEje;


     // --- Calculos de variables complejas ---
     Generador G(dat->Gen[0][0], dat->Gen[0][1], dat->Gen[0][2], dat->Gen[0][3]);
     G.setBaseNueva(dat->Gen[0][4], dat->Gen[0][5]);
     G.DiagVectorialGC(dat->Gen[0][6], dat->Gen[0][7], dat->Gen[0][8]);

     std::complex<double> V = G.getVOpu();
     std::complex<double> I = G.getIOpu();
     std::complex<double> RI = G.getVRpu();
     std::complex<double> XI = G.getVXpu();
     std::complex<double> E = G.getEGpu();
     double MagV = abs(V);
     double angV = arg(V)*180/M_PI;
     double MagI = abs(I);
     double angI = arg(I) * 180 / M_PI;
     double MagRI = abs(RI);
     double angRI = arg(RI) * 180 / M_PI;
     double MagXI = abs(XI);
     double angXI = arg(XI) * 180 / M_PI;
     double MagE = abs(E);
     double angE = arg(E) * 180 / M_PI;

     //Crear el texto con los valores de los vectores a ser mostrado en la ventana

     sf::Text text(fuente);
     text.setFont(fuente);
     text.setCharacterSize(14);
     text.setFillColor(sf::Color::Cyan); // Cambiamos el color a cian para variar
     text.setPosition({ 50.f, 50.f });

     // Convertir los números del vector a un solo String
     std::string contenidoVisual = "Vectores:\n";
     contenidoVisual += "- V = " + std::to_string(real(V)) + " +j" + std::to_string(imag(V));
     contenidoVisual += " = " + std::to_string(MagV) + " /_" + std::to_string(angV) + "°" + "\n";
     contenidoVisual += "- I = " + std::to_string(real(I)) + " +j" + std::to_string(imag(I));
     contenidoVisual += " = " + std::to_string(MagI) + " /_" + std::to_string(angI) + "°" + "\n";
     contenidoVisual += "-VR = " + std::to_string(real(RI)) + " +j" + std::to_string(imag(RI));
     contenidoVisual += " = " + std::to_string(MagRI) + " /_" + std::to_string(angRI) + "°" + "\n";
     contenidoVisual += "-VX = " + std::to_string(real(XI)) + " +j" + std::to_string(imag(XI));
     contenidoVisual += " = " + std::to_string(MagXI) + " /_" + std::to_string(angXI) + "°" + "\n";
     contenidoVisual += "-EG = " + std::to_string(real(E)) + " +j" + std::to_string(imag(E));
     contenidoVisual += " = " + std::to_string(MagE) + " /_" + std::to_string(angE) + "°" + "\n";
     
     text.setString(contenidoVisual);

     // --- Generaci�n y Encadenamiento Geom�trico de Vectores ---
     // Pasamos la variable 'fuente' para cumplir con las referencias de SFML 3

     // 1. Voltaje V: Nace en el centro
     VectorGrafico fasorV(centroVentana, real(V), imag(V), sf::Color::Cyan, "V", fuente);
     misVectores.push_back(fasorV);

     // 2. Corriente I: Nace en el centro como referencia de fase
     VectorGrafico fasorI(centroVentana, real(I), imag(I), sf::Color::Yellow, "I", fuente);
     misVectores.push_back(fasorI);

     // 3. Voltaje en R (RI): Nace en la punta de V
     VectorGrafico fasorRI(fasorV.destinoReal, real(RI), imag(RI), sf::Color::White, "R*I", fuente);
     if (G.getRa() != 0) {
     VectorGrafico fasorRI(fasorV.destinoReal, real(RI), imag(RI), sf::Color::Red, "R*I", fuente);
     misVectores.push_back(fasorRI);
     }
     
     // 4. Voltaje en X (XI): Nace en la punta de RI
     VectorGrafico fasorXI(fasorRI.destinoReal, real(XI), imag(XI), sf::Color::Green, "jX*I", fuente);
     misVectores.push_back(fasorXI);

     // 5. Voltaje resultante E: Nace en el centro y cierra con la punta de XI
     VectorGrafico fasorE(centroVentana, real(E), imag(E), sf::Color::Magenta, "E", fuente);
     misVectores.push_back(fasorE);


     // --- Control de visualizaci�n paso a paso ---
     size_t vectoresAMostrar = 1;

     // Bucle principal
     while (window.isOpen()) {
         while (const std::optional event = window.pollEvent()) {
             if (event->is<sf::Event::Closed>()) {
                 window.close();
             }

             if (const auto* mouseEvent = event->getIf<sf::Event::MouseButtonPressed>()) {
                 // Clic Derecho: Avanzar
                 if (mouseEvent->button == sf::Mouse::Button::Right) {
                     if (vectoresAMostrar < misVectores.size()) {
                         vectoresAMostrar++;
                     }
                     else {
                         vectoresAMostrar = 1;
                     }
                 }
                 // Clic Izquierdo: Retroceder
                 if (mouseEvent->button == sf::Mouse::Button::Left) {
                     if (vectoresAMostrar > 1) {
                         vectoresAMostrar--;
                     }
                     else {
                         vectoresAMostrar = misVectores.size();
                     }
                 }
             }
         }

         window.clear(sf::Color(20, 20, 20));

         // Dibujar los ejes de fondo
         window.draw(ejes);
         window.draw(text);

         // Dibujar los fasores permitidos
         for (size_t i = 0; i < vectoresAMostrar; ++i) {
             misVectores[i].dibujar(window);
         }

         window.display();
     }

 }