//
// Created by secre on 29/11/2024.
//

#ifndef PR1_MATERIAL_H
#define PR1_MATERIAL_H
namespace PAG{
    /**
     * Clase que contiene todoo lo relativo a un material, que se le asigna a un modelo
     * Color ambiente, color difuso, color especular, y exponente especular
     *
     * Lo anterior es para decir como se comporta el material al interactuar con la "luz"
     * Un material metalico brilla mucho, la madera no tanto ;) Para lograr eso se juega con los valores del color del material
     */
    class Material {
    private:
        float colorAmbiente[3] {0.1, 0.0, 0.0};
        float colorDifuso[3] {1.0, 0.0, 1.0}; //El color difuso, que es el que se ve al iluminar el modelo con dicho material
        float colorEspecular[3] {1.0, 0.0, 1.0};
        float exponenteEspecular = 100; //Esto es para decir como de rapido decrece la intensidad del material en un punto

    public:
        Material() = default;

        const float *getColorAmbiente() const;

        const float *getColorDifuso() const;

        const float *getColorEspecular() const;

        float getExponenteEspecular() const;
    };
}

#endif //PR1_MATERIAL_H
