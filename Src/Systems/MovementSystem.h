//
// Created by Manoloon on 26/05/2022.
//

#ifndef PIKUMAENGINE_MOVEMENTSYSTEM_H
#define PIKUMAENGINE_MOVEMENTSYSTEM_H
class MovementSystem: public System
        {
public:
    MovementSystem()
    {
        // RequireComponent<TransformComp>();
        //RequireComponent<...>();
    }
    void Update(float DeltaTime)
    {
        // for(auto entity : GetEntities())
        // {
        // Tick entity position based on its velocity
        //}
    }
        };
#endif //PIKUMAENGINE_MOVEMENTSYSTEM_H
