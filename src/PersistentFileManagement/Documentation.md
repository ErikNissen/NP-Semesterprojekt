# PersistentFileManagement

Die PersistentFileManagement-Klasse bietet Methoden zum Verwalten von Daten,
die in JSON-Dateien gespeichert sind.

## Konstruktor

``PersistentFileManagement(std::string name)``<br>
Erstellt ein neues PersistentFileManagement-Objekt.

#### Parameter
* ``name`` Der Name der Datei, in der die Daten gespeichert sind.

## Methoden
``save(const std::string& name)``<br>
Speichert das aktuelle Datenobjekt in einer Datei mit dem angegebenen Namen.
#### Parameter
* ``name`` Der Name der Datei, in die die Daten gespeichert werden sollen.

``save()``<br>
Speichert das aktuelle Datenobjekt in der Datei, deren Name beim Erstellen des Objekts angegeben wurde.

``load(const std::string& path)``<br>
Lädt ein JSON-Objekt aus einer Datei.
#### Parameter
* ``path`` Der Name zur Datei, aus der die Daten geladen werden sollen.
#### Rückgabewert
Ein ``nlohmann::json`` Objekt, das die Daten aus der Datei enthält.
#### Ausnahmen
Die Methode kann eine FileErrorException auslösen, wenn die angegebene Datei nicht vorhanden ist.

``get(const std::string& key)``<br>
Lädt ein bestimmtes Element aus dem Datenobjekt.
#### Parameter
* ``key`` Der Schlüssel des Elements, das abgerufen werden soll.
#### Rückgabewert
Ein ``nlohmann::json``-Objekt, das das angegebene Element enthält.

``remove(const std::string& key)``<br>
Löscht ein bestimmtes Element aus dem Datenobjekt.
#### Parameter
* ``key`` Der Schlüssel des Elements, das gelöscht werden soll.
#### Ausnahmen
Die Methode kann eine ``KeyErrorException`` auslösen, wenn der angegebene Schlüssel nicht im Datenobjekt vorhanden ist.

``purge()``<br>
Löscht alle Elemente aus dem Datenobjekt.

``create(const std::string& name)``<br>
Erstellt eine neue, leere Datei mit dem angegebenen Namen.
#### Parameter
* ``name`` Der Name der neuen Datei.
#### Ausnahmen
Die Methode kann eine ``FileErrorException`` auslösen, wenn die angegebene Datei bereits vorhanden ist.

``search(const std::string& search, bool key)``<br>
Sucht nach einem Schlüssel oder Wert.
#### Parameter
* ``search`` Der zu suchende Begriff.
* ``key`` Die Art der Suche (true = key, false = value)

``search(const std::regex& search, bool key)``<br>
Das selbe nur mit regex.
#### Parameter
* ``search`` Der zu suchende Begriff.
* ``key`` Die Art der Suche (true = key, false = value)

``update(const std::string& key, const std::string& value)``<br>
Aktualisiert die Wert des Schlüssels.
#### Parameter
* ``key`` Der zu aktualisierende Schlüssel.
* ``value`` Der Wert, der in den Schlüssel geschrieben werden soll.
#### Ausnahmen
Die Methode kann eine ``KeyErrorException`` auslösen, wenn der Schlüssel 
nicht vorhanden ist.

``add(const std::string& key, std::string value)``<br>
Erstellt einen Schlüssel mit einem Wert.
#### Parameter
* ``key`` Der zu erstellende Schlüssel.
* ``value`` Der Wert, der in den Schlüssel geschrieben werden soll.
#### Ausnahmen
Die Methode kann eine ``KeyErrorException`` auslösen, wenn der Schlüssel vorhanden ist.

``getData()``<br>
Gibt alle Daten aus.
#### Rückgabewert
Ein ``nlohmann::json``-Objekt, welches alle Daten enthält.

``setName(const std::string& name)``<br>
Setzt den Namen für die Datei.
#### Parameter
* ``name`` Der Name der Datei.