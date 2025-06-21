

#include "FloatingBox/HTTPRequestTypes.h"

void FBoxTransform::Dump() const
{
	if (location.Num() >= 3)
		UE_LOG(LogTemp, Log, TEXT("    Location: X=%.1f Y=%.1f Z=%.1f"), location[0], location[1], location[2]);

	if (rotation.Num() >= 3)
		UE_LOG(LogTemp, Log, TEXT("    Rotation: Pitch=%.1f Yaw=%.1f Roll=%.1f"), rotation[0], rotation[1], rotation[2]);

	if (scale.Num() >= 3)
		UE_LOG(LogTemp, Log, TEXT("    Scale: X=%.1f Y=%.1f Z=%.1f"), scale[0], scale[1], scale[2]);

}

void FBoxObject::Dump() const
{
	UE_LOG(LogTemp, Log, TEXT("  Type: %s"), *type);
	transform.Dump();
}

void FBoxType::Dump() const
{
	UE_LOG(LogTemp, Log, TEXT("  Name: %s"), *name);
	if (color.Num() >= 3)
		UE_LOG(LogTemp, Log, TEXT("  Color: R=%.0f G=%.0f B=%.0f"), color[0], color[1], color[2]);
	UE_LOG(LogTemp, Log, TEXT("  Health: %d"), health);
	UE_LOG(LogTemp, Log, TEXT("  Score: %d"), score);
}

void FBoxData::Dump() const
{
	UE_LOG(LogTemp, Warning, TEXT("=== Box Types (%d) ==="), types.Num());
	for (int32 i = 0; i < types.Num(); ++i)
	{
		UE_LOG(LogTemp, Warning, TEXT("BoxType [%d]:"), i);
		types[i].Dump();
	}

	UE_LOG(LogTemp, Warning, TEXT("=== Box Objects (%d) ==="), objects.Num());
	for (int32 i = 0; i < objects.Num(); ++i)
	{
		UE_LOG(LogTemp, Warning, TEXT("BoxObject [%d]:"), i);
		objects[i].Dump();
	}
}
