#include <afxwin.h>
#include <stdio.h>

// ����֧������ʱ����Ϣ����
class CAnimal:public CObject
{
	DECLARE_DYNAMIC(CAnimal)
};
IMPLEMENT_DYNAMIC(CAnimal,CObject)

class CDog:public CAnimal
{
	//DECLARE_DYNAMIC(CDog)
public: 
	static const CRuntimeClass classCDog; 
	virtual CRuntimeClass* GetRuntimeClass() const; 
};
//IMPLEMENT_DYNAMIC(CDog,CAnimal)
//IMPLEMENT_RUNTIMECLASS(CDog, CAnimal, 0xFFFF, NULL, NULL)
AFX_COMDAT const CRuntimeClass CDog::classCDog = 
{ 
	"CDog", //����
	sizeof(class CDog), //��С
	0xFFFF, //�汾
	NULL, 
	 ((CRuntimeClass*)(&CAnimal::classCAnimal)),//��һ���ڵ�ĵ�ַ���ڵ��ڸ��ࣩ
	//RUNTIME_CLASS(CAnimal), 
	NULL, 
	NULL 
}; 
CRuntimeClass* CDog::GetRuntimeClass() const 
{ 
	//return RUNTIME_CLASS(CDog);
	return ((CRuntimeClass*)(&CDog::classCDog));
}


int main()
{
	// 1 ��ȡ����ӡ���������Ϣ
	CDog dog;
	CRuntimeClass* pClass=dog.GetRuntimeClass();
	printf("������ƣ�%s,��Ĵ�С��%d,��İ汾:%d\n",
		pClass->m_lpszClassName,pClass->m_nObjectSize,pClass->m_wSchema);
	// 2 �ж϶����Ƿ�����ĳ����
	if (dog.IsKindOf(RUNTIME_CLASS(CWnd)))
	{
		printf("dog is a CWnd\n");
	} 
	else
	{
		printf("dog is not a CWnd\n");
	}
	return 0;
}