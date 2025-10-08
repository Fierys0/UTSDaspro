struct weaponData {
    int weaponID;
    char* weaponName;
    int damage;
    float critRate;
    float critDamage;
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
    int defense;
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
    int exp;
    int money;
    int statusEffect[4];
};


struct entityData Dragon = {
    01,
    "Dragon",
    1000,
    1000,
    struct weaponData Claws,
    struct weaponData noArmor,
    100,
    50,
    100,
    100,
    100,
}


struct entityData Slime = {
    02,
    "Slime",
    1000,
    1000,
    struct weaponData Claws,
    struct weaponData noArmor,
    100,
    50,
    100,
    100,
    100,
}
