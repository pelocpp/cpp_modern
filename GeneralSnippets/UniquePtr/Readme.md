# Unique Pointer

Das Beispiel demonstriert `std::unique_ptr`-Objekte am Beispiel einer fiktiven Window-Klasse.

Diese besitzt als Instanzvariablen zahlreiche graphische Steuerelemente, die dynamisch allokiert werden,
deren raw-Zeiger aber von `std::unique_ptr`-Objekte verwaltet werden.

Damit wird für all diese Steuerelemente der Destruktor automatisch aufgerufen.

Man beachte bei den verschiedenen Methoden `createDialog`, `showDialog` und `showAnotherDialog`:

Diese verschieben allesamt `std::unique_ptr`-Objekte, es erfolgen keine Kopiervorgänge.

Ein `std::unique_ptr`-Objekte kann per se auch nicht kopiert werden, dass wäre ein Widerspruch zu seiner Tätigkeit
("*exklusive Verwaltung eines raw-Zeigers*").

Damit kann man in Funktion showAnotherDialog einen Absturz beobachten, der zu Demonstrationszwecken eingebaut ist.

An dieser Stelle wäre der Gebrauch eines `std::shared_ptr`-Objekts sinnvoller.

