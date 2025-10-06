struct weaponData {
    int damage;
    int speed;
    int effect;
    char* weaponName;
    int weaponID;
};

struct armorData {
    int resistance;
    char* armorName;
    int armorID;
};

struct entityData {
    int entityID;
    int maxHealth;
    int health;
    char* name;
    struct weaponData weapon;
    struct armorData armor;
    int exp;
    int money;
};
