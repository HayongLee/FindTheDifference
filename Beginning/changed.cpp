
#include <windows.h>

// ���� ����
LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
HINSTANCE g_hInst;
LPSTR lpszClass="�ٲ�׸�ã�� Made By. �����";
HWND hWnd;

HBITMAP hBit; // Back Buffer�� �� ��Ʈ�����.
HBITMAP hBit_map;	// ���ȭ���� ����Ű�� ��Ʈ�����.
HBITMAP hBit_circle;	// ���׶�̸� ����Ű�� ��Ʈ�� ���,

//���� ���콺�� ��ǥ
int m_x;
int m_y;

//��� ������� �˾ƺ��� ����
int checked_point = 0;

//���� Ƚ�� 5ȸ

int failed_point = 5;

//���� ������� �˾ƺ��� ����
bool checked[3]; //0 : �ں���, 1 : Sonata Arctica, 2 : ������
bool istrue; //������ ���� ������ �ִ��� �ƴ��� �����ϴ� ��.
bool ending; //�������� �˸�

int limit_time = 10;
//���ѽð��� �ٷ�� ����.. 1�̻��� �ʱⰪ�� �־�� ���ư���.

int start_time_point = timeGetTime();
//�� �����Ҷ� �ð� ����...

int temp_time;//(timeGetTime()/1000) - (start_time_point/1000) �� �ٷ�� ����... �׳� �������� ���� ���� �귶������ �˷��ش�...

//������ ��ǥ �Է�

int point1[4] = { 507, 268, 552, 312 };//�ں���

int point2[4] = { 499, 336, 701, 385 }; //Sonata Arctica

int point3[4] = { 696, 152, 740, 276 }; //������


// Ŭ�� ���θ� ����Ű�� ����.
DWORD clicked = 0;

int LoadBmp( char* filename , HBITMAP* ArghBit)	// �׸������� �о�´�.
{


	HANDLE hFile;
	HBITMAP hBit;
	DWORD FileSize, dwRead;
	BITMAPFILEHEADER fh;
	BITMAPINFO * ih;
	PVOID pRaster;

	//������ ����.
	hFile = CreateFile( filename,GENERIC_READ,0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,
		NULL);
	if( hFile == INVALID_HANDLE_VALUE)
	{
		return 0;
	}

	// ���� ����� ���� ����ü (���� ���̺� ���� ) �� �о� ���δ�.
	ReadFile(hFile , &fh , sizeof(BITMAPFILEHEADER) , &dwRead, NULL);
	FileSize = fh.bfOffBits - sizeof(BITMAPFILEHEADER);
	ih = (BITMAPINFO *)malloc(FileSize);
	ReadFile(hFile, ih, FileSize, &dwRead, NULL);

	//DIB ������ ����� ���� �޸𸮸� �Ҵ��Ѵ�.
	hBit = CreateDIBSection(NULL,ih,DIB_RGB_COLORS, &pRaster, NULL , 0);
	//������ �����͸� �о���δ�.
	ReadFile(hFile , pRaster ,fh.bfSize - fh.bfOffBits, &dwRead , NULL);
	free(ih);
	CloseHandle(hFile);

	*ArghBit = hBit;

	return 1;
}

void Draw()
{
	
	char n, buf[1000];
	int temp_time = (timeGetTime()/1000) - (start_time_point/1000);
	
	limit_time = 10 - ((timeGetTime()/1000) - (start_time_point/1000));

	RECT crt;	// ���� â�� ������ �о�� ����.
	HDC hdc,hMemDC;

	GetClientRect(hWnd,&crt);	
	hdc=GetDC(hWnd);	


	if (hBit==NULL) {
		hBit=CreateCompatibleBitmap(hdc,crt.right,crt.bottom);
	}


	HDC MemDCBack = CreateCompatibleDC( hdc );


	HBITMAP OldBit_Back = (HBITMAP)SelectObject(MemDCBack, hBit);

	hMemDC=CreateCompatibleDC(MemDCBack);

	// ���ȭ���� ��Ʈ�� ����� hBit_map�� �Ʊ� ���� hMemDC�� �����Ѵ�.
	HBITMAP OldBit_Obj = (HBITMAP)SelectObject(hMemDC,hBit_map);

	BitBlt( MemDCBack , 0 , 0 , 800 , 600 , hMemDC , 0 , 0 , SRCCOPY);

	n = wsprintf(buf, "���� ���� : %d / 3    Life : %d / 5                                                                                                                     ���� �ð� : %d��       ", checked_point, failed_point, limit_time);
	TextOut( MemDCBack, 0, 400, buf, strlen(buf));

	// hMemDC�� ĳ���� ��Ʈ�� ����� ������.
	SelectObject(hMemDC, hBit_circle );
	

	
	if ( checked[0] == true ) //�ں��Ͽ� ���׶�� ǥ��
	{
		
		TransparentBlt( MemDCBack , 500, 260, 64, 64, hMemDC, 0, 0, 64, 64, RGB(100,0,100) );
		TransparentBlt( MemDCBack , 100, 260, 64, 64, hMemDC, 0, 0, 64, 64, RGB(100,0,100) );
	}
	if ( checked[1] == true ) //Sonata Arctica�� ���׶�� ǥ��
	{

		TransparentBlt( MemDCBack , 565, 333, 64, 64, hMemDC, 0, 0, 64, 64, RGB(100,0,100) );
		TransparentBlt( MemDCBack , 165, 333, 64, 64, hMemDC, 0, 0, 64, 64, RGB(100,0,100) );
	}
	if ( checked[2] == true ) //�������� ���׶�� ǥ��
	{
		TransparentBlt( MemDCBack , 690, 202, 64, 64, hMemDC, 0, 0, 64, 64, RGB(100,0,100) );
		TransparentBlt( MemDCBack , 290, 202, 64, 64, hMemDC, 0, 0, 64, 64, RGB(100,0,100) );
	}


	//limit_time = ((timeGetTime()/1000) - (start_time_point/1000));



	// hMemDC�� �����ִ� ��Ʈ�� ����� �ʱⰪ���� �ǵ����� �Ҹ��Ų��.
	SelectObject(hMemDC,OldBit_Obj);
	DeleteDC(hMemDC);

	// ����� DC�� ���� �ʱⰪ���� �ǵ����� �Ҹ��Ų��.
	SelectObject(MemDCBack,OldBit_Back);
	DeleteDC(MemDCBack);

	// �ƹ����� �Ǵ� dc���� hdc�� ������Ų��.
	ReleaseDC(hWnd,hdc);
	//InvalidateRect(hWndMain,NULL,FALSE);
}


void Flip()
{

	HDC hdc = GetDC( hWnd );
	HDC hMemDC=CreateCompatibleDC(hdc);

	RECT crt;
	GetClientRect(hWnd,&crt);	


    HBITMAP OldBit=(HBITMAP)SelectObject(hMemDC, hBit);

	BitBlt(hdc,0,0,crt.right,crt.bottom,hMemDC,0,0,SRCCOPY);

	// ����� �׳� �����ϴ� �κ�.
    SelectObject(hMemDC, OldBit);

	DeleteDC(hMemDC);
	ReleaseDC( hWnd, hdc );
}


void process()
{
	Draw();	// ���������� �׸��� �κ�.
	Flip();	// Draw���� Back Buffer�� �׸����� �׷ȱ� ������, ���⼭ ȭ��� Back Buffer�� �ٲ�ġ��(Flip)�ϴ� �κ��̴�.
}


int APIENTRY WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance
		  ,LPSTR lpszCmdParam,int nCmdShow)
{
	// ���� �ǵ��ʴ� ������ ����ü ����κ��̴�. ���� ���ٰ� ���� ����. �� �����ϰ� �Ѿ�� �ȴ�.

	MSG Message;
	WNDCLASS WndClass;
	g_hInst=hInstance;
	
	WndClass.cbClsExtra=0;
	WndClass.cbWndExtra=0;
	WndClass.hbrBackground=(HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.hCursor=LoadCursor(NULL,IDC_ARROW);
	WndClass.hIcon=LoadIcon(hInstance,IDI_APPLICATION);
	WndClass.hInstance=hInstance;
	WndClass.lpfnWndProc=(WNDPROC)WndProc;
	WndClass.lpszClassName=lpszClass;
	WndClass.lpszMenuName=NULL;
	WndClass.style=CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);

	hWnd=CreateWindow(lpszClass,lpszClass,WS_SYSMENU,
		  CW_USEDEFAULT,CW_USEDEFAULT,800,450,
		  NULL,(HMENU)NULL,hInstance,NULL);
	ShowWindow(hWnd,nCmdShow);

	// �׸������� �о�´�. �̸��׸� "bg.bmp"��� ������ hBit_map�̶�� ��Ʈ�� ����� ����ִ´ٴ� �ǹ��̴�.

	LoadBmp( "background.bmp", &hBit_map );
	LoadBmp( "circle.bmp", &hBit_circle );



	// �⺻ �޽��� �����Դϴ�.

	while( 1 )
	{
		// �ü���κ��� ���� �޽����� ������ �װ� ó���ϰ�,
		if( PeekMessage(&Message , NULL , 0 , 0 , PM_NOREMOVE) )
		{
			if(!GetMessage(&Message, NULL, 0, 0)) break ;
			TranslateMessage(&Message);
			DispatchMessage(&Message);
		}
		// ���� ���ٸ� �׸��� �׸��� ���� ������ �Ѵ�.
		else
		{
			process();
		}
		if ( checked_point == 3 ) // �� ���߸� ���α׷� ����
		{
			ending = true;
		}

		if ( failed_point == 0)// �� Ʋ���� ���α׷� ����
		{
			ending = true;
		}

		if ( ending == true && checked_point == 3 )
		{
			MessageBox(hWnd, TEXT("�����մϴ�. ��� ���߼̽��ϴ�."),
			TEXT("Cleared!!"), MB_OK);
			break;
		}
		else if ( ending == true && failed_point == 0 )
		{
			MessageBox(hWnd, TEXT("Oh My Shoulder!"),
			TEXT("Game Over"), MB_OK);
			break;
		}

		if ( limit_time == 0 )
		{
			MessageBox(hWnd, TEXT("��� �����մϴ�."),
			TEXT("Time Over!"), MB_OK);
			break;
		}

	}

	return Message.wParam;
}

void check_click_point()
{
	if ( m_x >= point1[0] && m_x <= point1[2] && m_y >= point1[1] && m_y <= point1[3])
	{	
		if ( checked[0] != true )
		{
			checked_point ++;
			checked[0] = true;
		}
		istrue = true;
	}//�ں��� ã���� - �ٸ� �׸�����

	else if ( m_x >= point2[0] && m_x <= point2[2] && m_y >= point2[1] && m_y <= point2[3] )
	{
		if ( checked[1] != true )
		{
			checked_point ++;
			checked[1] = true;
		}
		istrue = true;
	}//Sonata Arctica ã���� - �ٸ� �׸�����

	else if ( m_x >= point3[0] && m_x <= point3[2] && m_y >= point3[1] && m_y <= point3[3] )
	{
		if ( checked[2] != true )
		{
			checked_point ++;
			checked[2] = true;
		}
		istrue = true;
	}//������ ã���� - �ٸ� �׸�����
	
	else if ( m_x >= point1[0] - 400 && m_x <= point1[2] - 400 && m_y >= point1[1] && m_y <= point1[3] )
	{
		if ( checked[0] != true )
		{
			checked_point ++;
			checked[0] = true;
		}
		istrue = true;
	}//�ں��� ã���� - ���� �׸�����

	else if ( m_x >= point2[0] - 400 && m_x <= point2[2] - 400 && m_y >= point2[1] && m_y <= point2[3] )
	{
		if ( checked[1] != true )
		{
			checked_point ++;
			checked[1] = true;
		}
		istrue = true;
	}//Sonata Arctica ã���� - ���� �׸�����

	else if ( m_x >= point3[0] - 400 && m_x <= point3[2] - 400 && m_y >= point3[1] && m_y <= point3[3] )
	{
		if ( checked[2] != true )
		{
			checked_point ++;
			checked[2] = true;
		}
		istrue = true;
	}//������ ã���� - ���� �׸�����

	else
	{
		failed_point --;
		istrue = false;
	}


}

LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	switch(iMessage) {

	
	case WM_MOUSEMOVE:
		m_x = LOWORD(lParam);
		m_y = HIWORD(lParam);
		return 0;

	case WM_LBUTTONDOWN:
		clicked = timeGetTime();
		check_click_point();
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd,iMessage,wParam,lParam));
}
