#include "Item.h"


Item::Item(int o_peso, int o_beneficio)
{
  peso = o_peso;
  beneficio = o_beneficio;
}

void Item::setPeso(int o_peso)
{
  peso = o_peso;
}

void Item::setBeneficio(int o_beneficio)
{
  beneficio = o_beneficio;
}

void Item::setRatio(double o_ratio)
{
  ratio = o_ratio;
}

void Item::setPosition(bool o_position)
{
  position = o_position;
}
