struct weaponData {
    int weaponID;
    char* weaponName;
    int damage;
    int speed;
    int effect;
};

struct armorData {
    int armorID;
    char* armorName;
    int baseDefense;
    int resistance;
};

struct entityData {
    int entityID;
    char* name;
    int maxHealth;
    int health;
    struct weaponData weapon;
    struct armorData armor;
    int level;
    int baseDamage;
    int baseExpDrop;
    int baseMoneyDrop;
    float moneyMultiplier;
    float expMultiplier;
    int statusEffect[4];
};

struct Player {
    char* name;
    int maxHealth;
    int health;
    struct weaponData weapon;
    struct armorData armor;
    int level;
    int baseDamage;
    int magicPoint;
    int strengthPoint;
    int agilityPoint;
    int defensePoint;
    int statusEffect[4];
};
