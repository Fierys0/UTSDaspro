struct weaponData {
    int damage;
    int speed;
    int effect;
    char* weaponName;
}

struct armorData {
    int resistance;
}

struct entityData {
    int health;
    char* name;
    struct weaponData;
    struct armorData;
}

struct entityData Player;
Player.health = 100;
