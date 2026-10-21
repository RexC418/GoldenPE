#pragma once
#include <network/Packet.hpp>
#include <network/NetEventCallback.hpp>

struct StartGamePacket : Packet{
	int32_t seed, genver, gamemode, eid;
	int32_t terrainGenerator; //TerrainGeneratorType. Extra field at the end of the packet, the original game ignores it
	float x, y, z;
	StartGamePacket() {
		this->terrainGenerator = 0;
	}
	StartGamePacket(int seed, int genver, int gm, int eid, float x, float y, float z) {
		this->seed = seed;
		this->genver = genver;
		this->gamemode = gm;
		this->eid = eid;
		this->x = x;
		this->y = y;
		this->z = z;
		this->terrainGenerator = 0;
	}
	virtual ~StartGamePacket() {
	}
	virtual void write(RakNet::BitStream* stream) {
		stream->Write<uint8_t>(PID_START_GAME_PACKET);
		stream->Write<int32_t>(this->seed);
		stream->Write<int32_t>(this->genver);
		stream->Write<int32_t>(this->gamemode);
		stream->Write<int32_t>(this->eid);
		stream->Write<float>(this->x);
		stream->Write<float>(this->y);
		stream->Write<float>(this->z);
		stream->Write<int32_t>(this->terrainGenerator);
	}
	virtual void read(RakNet::BitStream* stream) {
		stream->Read<int32_t>(this->seed);
		stream->Read<int32_t>(this->genver);
		stream->Read<int32_t>(this->gamemode);
		stream->Read<int32_t>(this->eid);
		stream->Read<float>(this->x);
		stream->Read<float>(this->y);
		stream->Read<float>(this->z);
		//Packets of the original game don't have the extra field
		if(stream->GetNumberOfUnreadBits() >= 32) {
			stream->Read<int32_t>(this->terrainGenerator);
		} else {
			this->terrainGenerator = 0;
		}
	}
	virtual void handle(const RakNet::RakNetGUID& a2, NetEventCallback* a3) {
		a3->handle(a2, this);
	}
};
