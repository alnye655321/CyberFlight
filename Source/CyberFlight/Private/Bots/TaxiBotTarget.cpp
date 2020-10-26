// Copyright 2020 NyeDigital


#include "Bots/TaxiBotTarget.h"

ATaxiBotTarget::ATaxiBotTarget()
{

	TargetComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TargetComp"));
	TargetComp->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	CylinderComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CylinderComp"));
	CylinderComp->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

}
