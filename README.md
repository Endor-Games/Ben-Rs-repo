# Ben-Rs-repo

## Work For the Engine

### CSV Reading

All **CSV Files** read within the engine read identically to one another however will require diffrent Readers depending on what is needed to be loaded. These files can be edited in either Excel or Notepad however the latter is less recomended

#### Example of CSV file

```
Title  1 (String),Title2 2 (Int) Tile 3 (String)
<Text of first file>,1,<More Text>
<Text of Second file>,2,<Even More Text>
```

To read a String (Text) into the engine the text must start with < and and with >. Make sure not to use either of these unless declaring Text otherwise the system will crash.

#### Example

```<Text always goes betweem the brackets and, because of this, Commas can be used within the System.>```

Reading a integer into the system only requires a number and nothing else.
