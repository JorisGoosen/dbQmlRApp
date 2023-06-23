
library(dplyr);
con <- DBI::dbConnect(RSQLite::SQLite(), dbname = ':memory:');

DBI::dbExecute('CREATE TABLE RespiroData (id INTEGER PRIMARY KEY ASC, o2 INT, ch4 INT, co2 INT, pressure INT, temp1 REAL, temp2 REAL, utc INT);')
DBI::dbExecute('CREATE TABLE RespiroMsgs (id INTEGER PRIMARY KEY ASC, type TEXT, msg TEXT, utc INT);')

# hier kun je data toevoegen bijvoorbeeld

RespiroDatasql <- tbl(con, 'RespiroData');
'sql table is called: RespiroDatasql'
RespiroData <- RespiroDatasql %>% collect()

RespiroMsgssql <- tbl(con, 'RespiroMsgs');
'sql table is called: RespiroMsgssql'
RespiroMsgs <- RespiroMsgssql %>% collect()