# Systemnahe-Programmierung
Gruppenprojekt Systemnahe Programmierung

# Projektbeschreibung

## 1 Einleitung

Die dritte und vierte Portfolio-Prüfung in diesem Modul bestehen aus Softwareentwicklungsprojekten. In diesem Projekt müssen Sie nachweisen, dass Sie in der Lage sind, in einer kleinen Gruppe von 3 bis 4 Studierenden eine größere Software in C zu entwickeln.

## 2 Termine

Die Abgabefrist für Ihre Lösung ist Samstag, der 24. Januar 2026, um 18:00 Uhr (MEZ). Die Projektpräsentation findet während des Prüfungszeitraums statt. Das genaue Datum wird später im Semester bekannt gegeben, voraussichtlich erst im Dezember.

## 3 Motivation

Ein C-Projekt im Rahmen der Prüfung ermöglicht es Ihnen, echte Systemkompetenzen zu zeigen, nicht nur reines Faktenwissen. Durch das Entwerfen, Implementieren und Testen eines funktionierenden Programms demonstrieren Sie Ihre Beherrschung zentraler Themen – Speicherverwaltung und Pointer, Low-Level-I/O, Prozesse/Threads und performancebewusstes Programmieren – sowie den Einsatz von Debugging- und Entwicklungswerkzeugen.

Ein Projekt macht Ihr Verständnis sichtbar: Designentscheidungen, Fehlerbehandlung, Tests und Dokumentation zeigen, wie Sie als Systemprogrammierer denken. Es spiegelt zudem die Praxis wider, in der Korrektheit, Effizienz und Wartbarkeit gleichermaßen wichtig sind.

Kurz gesagt: Ihr Projekt ist der konkrete Beleg dafür, dass Sie Konzepte der systemorientierten Programmierung anwenden können, um zuverlässige Software zu schreiben, die hardwarenah arbeitet.

## 4 Technische Anforderungen

### 4.1 Quellcode in C:
- Der Quellcode muss in C geschrieben sein. Verwenden Sie aussagekräftige Datei- und Funktionsnamen. Das Projekt soll in mehrere Dateien mit Headern und Quellcode-Dateien (.h und .c) gegliedert sein. Übermäßige Kommentare sind nicht nötig, wenn der Code selbsterklärend ist. Sie können Kommentare hinzufügen, wenn der Code schwer verständlich ist. Eine technische Dokumentation ist optional und wird nicht bewertet.

### 4.2 Linux-Befehl implementieren:
- Das Programm soll eine vereinfachte Version eines Linux-Befehls (z. B. ls oder find) implementieren. Wir erwarten ca. 500 bis 1.500 Zeilen Code (nur grobe Richtwerte).

### 4.3 Dateisystem & Argumente:
- Die Software muss mit dem Dateisystem interagieren und benutzerdefinierte Argumente verarbeiten. Die Linux File API muss zum Lesen und Schreiben von Dateien verwendet werden. Kommandozeilenargumente sind Pflicht (z. B. Flags wie -l oder -r).

### 4.4 Dynamische Datenstrukturen:
- Verwenden Sie dynamische Datenstrukturen (z. B. Linked Lists, Queues oder Hash-Tabellen). Diese müssen korrekt alloziert und wieder freigegeben werden, um Speicherlecks zu vermeiden.

### 4.5 stdin & stdout:
- Das Programm soll Standard-Ein- und -Ausgabe unterstützen, damit es in Pipelines eingebunden werden kann.

### 4.6 Nebenläufigkeit (optional):
- Zur Verbesserung der Performance kann das Programm Threads nutzen, z. B. zur parallelen Verarbeitung mehrerer Verzeichnisse.

### 4.7 Synchronisation:
- Verwenden Sie Synchronisationsmechanismen (z. B. Semaphoren oder Mutexes), um bei parallelem Zugriff auf gemeinsame Ressourcen Thread-Sicherheit zu gewährleisten.

### 4.8 Build mit gcc & Makefile:
- Das Projekt muss mit gcc kompiliert werden. Ein Makefile ist Pflicht und muss Ziele für Build, Clean und Tests enthalten.

### 4.8 Commits im Repository:
- Das Repository muss eine angemessene Anzahl an Commits enthalten (mehr als 20, weniger als 1000 bei 500–1500 Zeilen Code). Es soll eine Entwicklung über die Zeit erkennbar sein. Beginnen Sie frühzeitig (idealerweise ab Ende Oktober) und committen Sie regelmäßig.

### Der Einsatz von Coding-Assistenten ist erlaubt. In diesem Fall müssen diese genannt und ihr Einsatz beschrieben werden (in der README-Datei).

## 5 Abgabe bis 24.01.2026

Folgende Unterlagen müssen bis zum 24. Januar 2026 eingereicht werden:

### 5.1 Git-Repository

- Ein Git-Repository (z. B. auf THWS GitLab oder einer anderen Plattform), das den vollständigen Code inkl. Tests enthält. Im Root-Verzeichnis muss eine README liegen, die erklärt, wie man das Projekt startet und die Tests ausführt.

### 6.2 Screencast (ca. 5 Minuten)

- Ein Video, das Ihr Projekt demonstriert.
- Anforderungen:
- MP4-Format
- Mindestauflösung: 720p (1080p empfohlen)
- Maximale Größe: 20 MB
- Muss Ton enthalten (Gesicht zeigen ist nicht nötig)
- Keine Titel- oder Abschiedsfolie, keine Musik
- Keine Folien nötig
- Begrüßung („Hi“) wäre nett
- Abspielbar in VLC oder QuickTime
- Vor Abgabe Qualität prüfen
- Eigene Aufnahme (kein fremdes Material)

### 5.3 Textdatei für Moodle

- Reichen Sie eine reine Textdatei (kein Word/PDF) ein, die enthält:
- URL zum Repository
- URL zum Video
- Matrikelnummern aller Beteiligten (durch Komma getrennt)

Beispiel:
https://git.fiw.thws.de/sop/mycoolproject
https://www.youtube.com/watch?v=CLi6YIWXkQI
5123007, 5123008, 5223001

## 6 Projektpräsentation im Prüfungszeitraum

- Gruppenpräsentation auf Englisch (ca. 10 Minuten) mit Folien
- Fokus liegt auf der Implementierung, nicht auf der Ausführung
- Darstellung der Softwarearchitektur und der schwierigsten Algorithmen
- Anschließend Fragerunde (weitere ca. 10 Minuten), jede Person muss ihren Code erklären können
- Laptop, Code und Entwicklungsumgebung mitbringen
- Bonuspunkte für Nutzung von Linux & NeoVim

## 7 Bewertung

Maximalpunkte:

- 27 Punkte für Implementierung
- 22,5 Punkte für Präsentation

Ablauf:

1. Repository wird geklont
2. Keine Commits nach Deadline erlaubt
3. README wird geprüft
4. Video wird angesehen
5. Quellcode wird analysiert
6. Präsentation & Antworten werden bewertet
