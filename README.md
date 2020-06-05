# Ben-Rs-repo

## Work For the Engine

### CSV Reading

All **CSV Files** read within the engine read identically to one another however will require different Readers depending on what is needed to be loaded. These files can be edited in either Excel or Notepad however the latter is less recommended. 

#### Example of CSV file

```
Title  1 (String),Title2 2 (Int) Tile 3 (String)
<Text of first file>,1,<More Text>
<Text of Second file>,2,<Even More Text>
```

To read a String (Text) into the engine the text must start with < and and with >. Make sure not to use either of these unless declaring Text otherwise the system will crash.

#### Example
```
<Text always goes between the brackets and, because of this, Commas can be used within the System.>
```

Reading a integer into the system only requires a number and nothing else.


### CSV Example 1 Dialogue
Dialogue is Split into 10 Columns.

- **Name:** The Name that will be displayed for the piece of dialogue (Example John Smith)

- **Dialogue:** The Main body of text that will be displayed usually said to the player

- **Response_Text_0-3:** The Text that will appear in a button, usually used as a response to what was said in Dialogue. If a dialogue option is not needed it can be removed by placing **<n/a>** in the place of actual dialogue. If this is used on **Response_Text_0** The text will be changed to "Next" in order to allow a single option.

- **Response_ID_0-3:** The Location of the next piece of dialogue within the CSV, the ID starts at 0 from line 2 in an Excel Document (line 1 is used for explaining each column and is ignored by the system). If <n/a> is used in **Response_Text_0** the Response ID will be defaulted to the ID of the row being read in plus 1.

### CSV Example 2 Enemies
Enemies are Split into 20 columns

- **Name:** The Name of the enemy that will be fought
- **Sprite:** The Location of the Sprite that will be used for the enemy (Sprites are not currently loading in so the data structure will only hold the possible location)
- **Death Sound:** The Location of the Sound that will play when the enemy is defeated
- **Encounter Rate:** The Chance of encountering this enemy in the wild
- **Level:** The level that is required to start encountering this enemy (5 levels above or bellow)
- **HP:** How much damage is required to defeat the enemy
- **Attack** Overall Strength of the enemy
- **Defence:** ??
- **Speed:** Determines the turn order for when the enemy will attack (If the enemy’s speed is higher than the players speed the enemy will attack first.

- **Attack Name_0 to 2:** The name of the attack that may be declared (attack 1 or 2 are un-needed write use <n/a> in the text no other information will be needed within the row after declaration)
- **Attack Damage_0 to 2:** The amount of damage that will be dealt by the specified attack
- **Attack Sound_0 to 2:** The Location of the sound that will play when the enemy uses the specified attack
- **Attack Rate_0 to 2:** How Often the attack will be used when compared to other attacks the enemy may have.

