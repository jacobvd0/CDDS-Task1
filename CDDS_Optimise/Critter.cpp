#include "Critter.h"
#include "HashTable.h"
#include <iostream>


Critter::Critter()
{
	m_position = Vector2{ 0, 0 };
	m_velocity = Vector2{ 0, 0 };
	m_radius = 0;
	m_isLoaded = false;
}

Critter::~Critter()
{
	m_isLoaded = false;
}

void Critter::Init(Vector2 position, Vector2 velocity, float radius, const char* texture, HashTable* hashTable)
{
	m_position = position;
	m_velocity = velocity;
	m_radius = radius;
	
	m_texture = (hashTable->operator[](texture));

	m_isLoaded = true;
}

void Critter::Destroy()
{
	m_texture = nullptr;
	m_isLoaded = false;
}

void Critter::Update(float dt)
{
	if (m_isLoaded == false)
		return;

	m_position.x += m_velocity.x * dt;
	m_position.y += m_velocity.y * dt;

	m_isDirty = false;
}


void Critter::Draw()
{
	if (m_isLoaded == false) {
		std::cout << "NOT LOADED\n";
		return;
	}
		
	
	DrawTexturePro(*m_texture, { 0, 0, (float)m_texture->width, (float)m_texture->height }, { m_position.x, m_position.y, (float)m_texture->width, (float)m_texture->height }, {origin.x * m_texture->width, origin.y * m_texture->height }, 0.0f, WHITE);
}

Vector2 Critter::OriginTest(float spriteWidth, float spriteHeight)
{
	return { origin.x * spriteWidth, origin.y * spriteHeight };
}

