Entity *loadPlayer(int, int, char *);
void setPlayerLocation(int, int);
void doPlayer(void);
void drawPlayer(void);
void setPlayerShield(int);
void setPlayerWeapon(int);
void autoSetPlayerWeapon(Entity *);
void autoSetPlayerShield(Entity *);
int getDistanceFromPlayer(Entity *);
void writePlayerToFile(FILE *);
void setPlayerWeaponName(char *);
void setPlayerShieldName(char *);
void playerWaitForDialog(void);
void playerResumeNormal(void);
void writePlayerMapStartToFile(FILE *);
