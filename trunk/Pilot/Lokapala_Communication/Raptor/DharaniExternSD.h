/**@file	DharaniExternSD.h
 * @brief	Dharani ������Ʈ�κ��� �ܺη��� SD�� ����.
 * @author	siva
 */

#ifndef DHARANI_EXTERN_SD_H
#define DHARANI_EXTERN_SD_H

/**@ingroup	GroupDharani
 * @class	CDharaniExternSD
 * @brief	Dharani ������Ʈ�κ��� �ܺη��� SD. Dharani ������Ʈ�� ����ϴ� Ŭ���̾�Ʈ ������ �ϼ��ؾ� �Ѵ�.\n
 *			Dharani���� Ŭ���̾�Ʈ �������� ��� �������� ���ȴ�. ��ü�����δ� Read�� ������ �˸� �� ���ȴ�.
 */
class CDharaniExternSD
{
public :
	static CDharaniExternSD *Instance()
	{
		if(!m_instance)
		{
			m_instance = new CDharaniExternSD();
		}
		return m_instance;
	}
	void NotifyAccepted();
	void NotifyLeft();
	void NotifyReceived(char *a_receivedMessage);	

protected :
	CDharaniExternSD(){};
	~CDharaniExternSD(){};

private :
	static CDharaniExternSD *m_instance;

};


#endif