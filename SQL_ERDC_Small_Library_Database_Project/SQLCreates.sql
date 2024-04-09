CREATE TABLE Wydawnictwa (
    Id INT PRIMARY KEY CHECK (Id <= 500 AND Id > 0),
	Nazwa NVARCHAR(30) CHECK (LEN(Nazwa) BETWEEN 2 AND 30 ) NOT NULL,
	Kraj VARCHAR(50) CHECK ( Kraj LIKE N'[A-Z]%' AND LEN(Kraj) BETWEEN 2 AND 50 ) NOT NULL,
	Numer_budynku INT CHECK (Numer_budynku <= 1000 AND Numer_budynku > 0) NOT NULL,
	Ulica NVARCHAR(50) CHECK (LEN(Ulica) BETWEEN 5 AND 50 ) NOT NULL,
	Kod_pocztowy VARCHAR(6) CHECK ( Kod_pocztowy LIKE '[0-9][0-9]-[0-9][0-9][0-9]' ) NOT NULL,
	Miejscowosc NVARCHAR(50) CHECK ( Miejscowosc LIKE N'[A-Z]%' AND LEN(Miejscowosc) BETWEEN 2 AND 50 ) NOT NULL
);

CREATE TABLE Ksiazki (
    ISBN VARCHAR(13) PRIMARY KEY CHECK ( ISBN LIKE '[0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9]' OR ISBN LIKE '[0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9]'),
    Tytul NVARCHAR(50) CHECK (LEN(Tytul) BETWEEN 1 AND 50 ) NOT NULL,
	Rok_Wydania INT CHECK ( Rok_Wydania <= YEAR(GETDATE()) AND Rok_Wydania > 0) NOT NULL,
	Cena DECIMAL(5, 2) NOT NULL,
	Wydawnictwo INT NOT NULL,
	FOREIGN KEY (Wydawnictwo) REFERENCES Wydawnictwa(Id)
);

CREATE TABLE Autorzy (
    Id INT PRIMARY KEY CHECK(Id <= 5000 AND Id > 0),
    Imie NVARCHAR(50) CHECK ( Imie LIKE N'[A-Z,•, ,∆,—,è,Ø,”]%'  AND (Imie NOT LIKE N'%[^A-Za-z, ,•, ,∆,—,è,Ø,”,π,Í,Ê,Ò,ø,ü,Û]%') AND LEN(Imie) BETWEEN 2 AND 50 ) NOT NULL,
    Nazwisko NVARCHAR(50) CHECK (Nazwisko LIKE N'[A-Z,•, ,∆,—,è,Ø,”]%' AND (NAZWISKO NOT LIKE N'%[^A-Za-z, ,•, ,∆,—,è,Ø,”,π,Í,Ê,Ò,ø,ü,Û]%') AND LEN(Nazwisko) BETWEEN 2 AND 50 ) NOT NULL,
	Pseudonim NVARCHAR(50) CHECK (LEN(Pseudonim) BETWEEN 2 AND 50 ),
	Kraj_pochodzenia VARCHAR(50) CHECK ( Kraj_pochodzenia LIKE N'[A-Z]%' AND LEN(Kraj_pochodzenia) BETWEEN 2 AND 50 ) NOT NULL
);

CREATE TABLE Autorzy_ksiazek (
    Ksiazka VARCHAR(13) NOT NULL,
    Autor INT NOT NULL,
	FOREIGN KEY (Ksiazka) REFERENCES Ksiazki(ISBN) ON UPDATE CASCADE ON DELETE CASCADE,
	FOREIGN KEY (Autor) REFERENCES Autorzy(Id)
);

CREATE TABLE Hurtownie (
    Id INT PRIMARY KEY CHECK(Id <= 25 AND Id > 0),
	Nazwa NVARCHAR(50) CHECK (LEN(Nazwa) BETWEEN 2 AND 50 ) NOT NULL,
	Kraj VARCHAR(50) CHECK ( Kraj LIKE N'[A-Z]%' AND LEN(Kraj) BETWEEN 2 AND 50 ) NOT NULL,
	Numer_budynku INT CHECK (Numer_budynku <= 1000 AND Numer_budynku > 0) NOT NULL,
	Ulica NVARCHAR(50) CHECK (LEN(Ulica) BETWEEN 5 AND 50 ) NOT NULL,
	Kod_pocztowy VARCHAR(6) CHECK ( Kod_pocztowy LIKE '[0-9][0-9]-[0-9][0-9][0-9]' ) NOT NULL,
	Miejscowosc NVARCHAR(50) CHECK ( Miejscowosc LIKE N'[A-Z]%' AND LEN(Miejscowosc) BETWEEN 2 AND 50 ) NOT NULL
);

CREATE TABLE Zamowienia (
    Id INT PRIMARY KEY CHECK (Id <= 2000 AND Id > 0),
	Stan VARCHAR(20) CHECK (Stan LIKE ('dostarczone') OR Stan LIKE ('anulowane') OR Stan LIKE ('w trakcie realizacji')) NOT NULL,
	Data_zlozenia DATE NOT NULL,
	Wykonawca INT NOT NULL,
	FOREIGN KEY (Wykonawca) REFERENCES Hurtownie(Id)

);

CREATE TABLE Sprzedaze (
    Id INT PRIMARY KEY CHECK (Id <= 5000 AND Id > 0),
	Data_sprzedazy DATE NOT NULL,
);

CREATE TABLE Dostawy (
    Id INT PRIMARY KEY CHECK (Id <= 2000 AND Id > 0),
	Data_przyjecia DATE NOT NULL,
);

CREATE TABLE Pozycje_zamowien (
    Id INT PRIMARY KEY CHECK (Id <= 10000 AND Id > 0),
	Cena DECIMAL(5, 2) NOT NULL,
	Ilosc_zamowiona INT NOT NULL,
	Zamowiona_ksiazka VARCHAR(13) NOT NULL,
	Nr_zamowienia INT NOT NULL,
	FOREIGN KEY (Zamowiona_ksiazka) REFERENCES ksiazki(ISBN) ON UPDATE CASCADE ON DELETE CASCADE,
	FOREIGN KEY (Nr_zamowienia) REFERENCES Zamowienia(Id)
);

CREATE TABLE Pozycje_sprzedazy (
    Id INT PRIMARY KEY CHECK (Id <= 10000 AND Id > 0),
	Cena_jednostkowa DECIMAL(5, 2) NOT NULL,
	Rabat DECIMAL(5, 2) NOT NULL,
	Ilosc INT NOT NULL,
	Kupiona_ksiazka VARCHAR(13) NOT NULL,
	Nr_sprzedazy INT NOT NULL,
	FOREIGN KEY (Kupiona_ksiazka) REFERENCES Ksiazki(ISBN) ON UPDATE CASCADE ON DELETE CASCADE,
	FOREIGN KEY (Nr_sprzedazy) REFERENCES Sprzedaze(Id)
);

CREATE TABLE Pozycje_Dostawy (
    Id INT PRIMARY KEY CHECK (Id <= 10000 AND Id > 0),
	Ilosc_dostarczona INT NOT NULL,
	Nr_dostawy INT NOT NULL,
	Nr_wypelnianej_pozycji INT NOT NULL,
	FOREIGN KEY (Nr_dostawy) REFERENCES Dostawy(Id),
	FOREIGN KEY (Nr_wypelnianej_pozycji) REFERENCES Pozycje_zamowien(Id) ON DELETE CASCADE
);