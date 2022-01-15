// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InputHandlerInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInputHandlerInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class TRAVELER_API IInputHandlerInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void VGoForward() PURE_VIRTUAL(IInputHandlerInterface::VGoForward,);
	virtual void VGoRight()  PURE_VIRTUAL(IInputHandlerInterface::VGoRight, );

	virtual void VCameraPitch()  PURE_VIRTUAL(IInputHandlerInterface::VCameraPitch, );
	virtual void VCameraYaw()  PURE_VIRTUAL(IInputHandlerInterface::VCameraYaw, );
	virtual void VCameraZoomInOut()  PURE_VIRTUAL(IInputHandlerInterface::VCameraZoomInOut, );

	virtual void VPressButtonJump()  PURE_VIRTUAL(IInputHandlerInterface::VPressButtonJump, );
	virtual void VReleaseButtonJump()  PURE_VIRTUAL(IInputHandlerInterface::VReleaseButtonJump, );

	virtual void VPressButtonSprint()  PURE_VIRTUAL(IInputHandlerInterface::VPressButtonSprint, );
	virtual void VReleaseButtonSprint() PURE_VIRTUAL(IInputHandlerInterface::VReleaseButtonSprint, );

	virtual void VPressButtonDodge()  PURE_VIRTUAL(IInputHandlerInterface::VPressButtonDodge, );
	virtual void VReleaseButtonDodge()  PURE_VIRTUAL(IInputHandlerInterface::VReleaseButtonDodge, );

	virtual void VPressButtonFire()  PURE_VIRTUAL(IInputHandlerInterface::VPressButtonFire, );
	virtual void VReleaseButtonFire()  PURE_VIRTUAL(IInputHandlerInterface::VReleaseButtonFire, );

	virtual void VPressButtonAim()  PURE_VIRTUAL(IInputHandlerInterface::VPressButtonAim, );
	virtual void VReleaseButtonAim()  PURE_VIRTUAL(IInputHandlerInterface::VReleaseButtonAim, );

	virtual void VPressButtonAction1()  PURE_VIRTUAL(IInputHandlerInterface::VPressButtonAction1, );
	virtual void VReleaseButtonAction1() PURE_VIRTUAL(IInputHandlerInterface::VReleaseButtonAction1, );

	virtual void VPressButtonAction2()  PURE_VIRTUAL(IInputHandlerInterface::VPressButtonAction2, );
	virtual void VReleaseButtonAction2()  PURE_VIRTUAL(IInputHandlerInterface::VReleaseButtonAction2, );

	virtual void VPressButtonAction3()  PURE_VIRTUAL(IInputHandlerInterface::VPressButtonAction3, );
	virtual void VReleaseButtonAction3() PURE_VIRTUAL(IInputHandlerInterface::VReleaseButtonAction3, );

	virtual void VPressButtonAction4() PURE_VIRTUAL(VPressButtonAction4::VPressButtonAction4, );
	virtual void VReleaseButtonAction4() PURE_VIRTUAL(VReleaseButtonAction4::VReleaseButtonAction4, );
};
