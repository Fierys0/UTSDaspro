struct weaponData {
    int damage;
    int speed;
    int effect;
    char* weaponName;
};

struct armorData {
    int resistance;
    char* armorName;
};

struct entityData {
    int maxHealth;
    int health;
    char* name;
    struct weaponData weapon;
    struct armorData armor;
};
