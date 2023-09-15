#pragma once
#include <qvectornd.h>

/*static*/ class Color
{
public:
	/*
	Behold the color of passion, of love and of fire.
	A hue so rich and deep, like a rose in bloom or 
	a ruby glowing in the sun. But beware, for like
	flames that flicker in the night, it can consume 
	and destroy all that is in its path.
	*/
	static inline QVector3D Red = QVector3D(1.f, 0.f, 0.f);

	/*
	A verdant color, the color of life and nature.
	It speaks of growth and vitality, of the lush
	forests and rolling hills that cover our world.
	But do not be deceived, for like the ivy that
	creeps and entangles, it can hide danger and 
	destruction within its embrace.
	*/
	static inline QVector3D Green = QVector3D(0.f, 1.f, 0.f);

	/*
	The color of the deep and endless sea, of the 
	sky that stretches beyond our reach. A hue that
	conjures images of calm and serenity, of peace
	and tranquility. Yet beware, for like the ocean
	that churns and thrashes, it can hold within it
	the tempest and the storm.
	*/
	static inline QVector3D Blue = QVector3D(0.f, 0.f, 1.f);

	/*
	A hue that glows like the sun, bright and warm
	and full of life. It speaks of joy and happiness,
	of the golden fields that stretch out before us.
	But like the sun that beats down upon us, it can
	also burn and scorch, leaving only desolation 
	in its wake.
	*/
	static inline QVector3D Yellow = QVector3D(1.f, 1.f, 0.f);

	/*
	A regal color, fit for kings and queens. It speaks 
	of luxury and opulence, of a richness beyond compare.
	But do not be fooled, for like the velvet curtain 
	that hides the true nature of the stage, it can 
	conceal darkness and deception.
	*/
	static inline QVector3D Purple = QVector3D(0.5f, 0.f, 0.5f);

	/*
	A hue that shimmers like the surface of a pool, 
	clear and bright and full of life. It speaks of 
	innocence and purity, of a world untouched by 
	the stains of sin. But like the waters that
	ebb and flow, it can also conceal danger and 
	chaos beneath its surface.
	*/
	static inline QVector3D Cyan = QVector3D(0.f, 1.f, 1.f);

	/*
	A color that sings of sweetness and romance, of 
	flowers in full bloom and young love in its prime.
	It speaks of tenderness and affection, of a 
	gentleness that can heal the deepest of wounds.
	But like the rose with its thorns, it can also 
	wound and prick, leaving behind only pain and
	heartache.
	*/
	static inline QVector3D Pink = QVector3D(1.f, 0.75f, 0.8f);
	/*
	A fiery color, the color of the setting sun as it 
	casts its final rays across the sky. It speaks of 
	warmth and energy, of a vitality that can ignite 
	the passions of those around it. But like the 
	embers that smolder and die, it can also fade 
	away into nothingness, leaving behind only 
	ashes and dust.
	*/
	static inline QVector3D Orange = QVector3D(1.f, 0.5f, 0.f);

	/*
	A pure and brilliant hue, like a freshly fallen
	snow or a sheet of pristine paper. It speaks of
	innocence and purity, of a world untouched by
	the stains of sin. But beware, for like the
	shadows that dance in the light, it can also
	reveal the flaws and imperfections that lurk
	beneath the surface.
	*/
	static inline QVector3D White = QVector3D(1.f, 1.f, 1.f);

	/*
	A color that is as old as time, as deep and 
	eternal as the void of space. It speaks of 
	mystery and secrecy, of the unknown and the 
	unseen. But be wary, for like the darkness that 
	envelops us, it can also conceal the dangers that
	lurk in the shadows, waiting to pounce when we
	least expect it.
	*/
	static inline QVector3D Black = QVector3D(0.f, 0.f, 0.f);
};
