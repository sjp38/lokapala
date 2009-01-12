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
	void NotifyAccepted(in_addr *a_clientIp, in_addr *a_localIp);
	void NotifyLeft(in_addr *a_globalIP, in_addr *a_localIp);
	void NotifyReceived(char *a_receivedMessage);
	void NotifyReceived(char *a_receivedMessage, in_addr a_clientIp, in_addr a_localIp);	

protected :
	CDharaniExternSD(){};
	~CDharaniExternSD(){};

private :
	static CDharaniExternSD *m_instance;

};


#endif