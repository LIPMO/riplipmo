#pragma once
#include "../../../Packet/Packet.h"
class C07PacketPlayerDigging : public Packet
{
public:
	using Packet::Packet;

	static C07PacketPlayerDigging new_object(int action, int block_x, int block_y, int block_z, int side, JNIEnv* env = Ripterms::p_env);
protected:
	inline static Ripterms::JavaClassV2 C07PacketPlayerDiggingClass{ "net/minecraft/network/play/client/C07PacketPlayerDigging" };
};