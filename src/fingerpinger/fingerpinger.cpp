// ==============================================================================
// fingerpinger.cpp
//	
// tracking fingers on a macbook trackpad
//
// flext port:
// Author: Christian Frisson
// Copyright: 2010 numediart
// Website: www.numediart.org
//
// based on Max object by:	
// Authors:	Michael & Max Egger
// Copyright: 2009 [ a n y m a ]
// Website:	www.anyma.ch
//
// based on code by: http://www.steike.com/code/multitouch/
//	
// License: GNU GPL 2.0 www.gnu.org
//	
// Version: 2010-02-01
// ==============================================================================

#include <flext.h>

#if !defined(FLEXT_VERSION) || (FLEXT_VERSION < 401)
#error You need at least flext version 0.4.1
#endif

#include <math.h>
#include <stdlib.h>
#include <string>
#include <unistd.h>
#include <assert.h>
#include <vector>
#include <algorithm>
#include <CoreFoundation/CoreFoundation.h>
#include "MultitouchSupport.h"

static MTDeviceRef dev;								// reference to the trackpad

class fingerpinger:
	public flext_base
	{
		FLEXT_HEADER(fingerpinger,flext_base)
		
	public:
		fingerpinger();
		~fingerpinger();
		
	protected:
		void m_enable(int status);

	public:
		int m_fingers;		

	private:
		FLEXT_CALLBACK_I(m_enable);
	};

// instantiate the class (constructor has a variable argument list)
// note the two words in the string: prepend acts as an alias for fingerpinger!
FLEXT_NEW("fingerpinger",fingerpinger)

static std::vector<fingerpinger*> instances;

static int callback(int device, Finger *data, int nFingers, double timestamp, int frame)
{

	flext_base::AtomList myList(12);
	for (std::vector<fingerpinger*>::const_iterator it = instances.begin(); it != instances.end(); ++it)
	{
		if ( (*it)->m_fingers != nFingers) {
			#if FLEXT_SYS == FLEXT_SYS_PD
			(*it)->ToOutInt(1,nFingers);
			#endif
			(*it)->m_fingers = nFingers;
		}
		#if FLEXT_SYS == FLEXT_SYS_MAX
		(*it)->ToOutBang(1);
		#endif
	}
	for (int i=0; i < nFingers; i++) {
		Finger *f = &data[i];
		flext_base::SetFloat(myList[0],(float)(i));
		flext_base::SetFloat(myList[1],(float)(f->frame));
		flext_base::SetFloat(myList[2],(float)(f->angle));
		flext_base::SetFloat(myList[3],(float)(f->majorAxis));
		flext_base::SetFloat(myList[4],(float)(f->minorAxis));
		flext_base::SetFloat(myList[5],(float)(f->normalized.pos.x));
		flext_base::SetFloat(myList[6],(float)(f->normalized.pos.y));
		flext_base::SetFloat(myList[7],(float)(f->normalized.vel.x));
		flext_base::SetFloat(myList[8],(float)(f->normalized.vel.y));
		flext_base::SetFloat(myList[9],(float)(f->identifier));
		flext_base::SetFloat(myList[10],(float)(f->state));
		flext_base::SetFloat(myList[11],(float)(f->size));

		for (std::vector<fingerpinger*>::const_iterator it = instances.begin(); it != instances.end(); ++it)
			(*it)->ToOutList(0,myList);
	}
	return 0;
}

fingerpinger::fingerpinger()
: m_fingers(0)
{ 
	AddInAnything();
	AddOutAnything();
	#if FLEXT_SYS == FLEXT_SYS_PD
		AddOutInt();
	#endif
	#if FLEXT_SYS == FLEXT_SYS_MAX
		AddOutBang();
	#endif

	// register method
	FLEXT_ADDMETHOD(0,m_enable);
	
	post("%s - steike (Erling Ellingsen): initial code",thisName());
	post("%s - [ a n y m a ] (Michael & Max Egger): Max object",thisName());
	post("%s - numediart (Christian Frisson): flext port",thisName());
} 

fingerpinger::~fingerpinger()
{
	m_enable(0);
}

void fingerpinger::m_enable(int status)
{
	if (status == 1)
	{
		if (instances.empty()) {
			dev = MTDeviceCreateDefault();
			MTRegisterContactFrameCallback(dev, callback);
			MTDeviceStart(dev, 0);
		}
		if (find(instances.begin(), instances.end(), this) == instances.end())
			instances.push_back(this);
	}
	else
	{
		std::vector<fingerpinger*>::iterator it = find(instances.begin(), instances.end(), this);
		if (it != instances.end())
			instances.erase(it);
		assert(find(instances.begin(), instances.end(), this) == instances.end());
		if (instances.empty()) {
			MTUnregisterContactFrameCallback(dev, callback);
			MTDeviceStop(dev);
			MTDeviceRelease(dev);
			dev = NULL;
		}	
	}	
}