/**@file	DharaniExternSD.h
 * @brief	Dharani 컴포넌트로부터 외부로의 SD를 정의.
 * @author	siva
 */

#ifndef DHARANI_EXTERN_SD_H
#define DHARANI_EXTERN_SD_H

/**@ingroup	GroupDharani
 * @class	CDharaniExternSD
 * @brief	Dharani 컴포넌트로부터 외부로의 SD. Dharani 컴포넌트를 사용하는 클라이언트 측에서 완성해야 한다.\n
 *			Dharani에서 클라이언트 측으로의 통신 수단으로 사용된다. 구체적으로는 Read한 사항을 알릴 때 사용된다.
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
