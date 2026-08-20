//
// Created by Manoloon on 03/07/2022.
//
#pragma once

enum class ERenderLayers
{
    L_BACKGROUND,
    L_TILEMAP,
    L_OBSTACLES,
    L_ENEMIES,
    L_PROJECTILE,
    L_PLAYER,
    L_FOREGROUND,
    L_GUI
};

enum class EEntityGroups
{
    G_Player,
    G_Enemies,
    G_Projectile,
    G_Tiles,
    G_UI
};