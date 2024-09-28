#include "mongoose.h"  // Sicherstellen, dass "mongoose.h" im selben Verzeichnis liegt

// JSON-Antwort, die für /test gesendet wird
static const char *s_response = "{ \"message\": \"Hello, this is a test response\" }";

// HTTP-Event-Handler Funktion für eingehende Anfragen
static void handle_request(struct mg_connection *c, int ev, void *ev_data) {
  if (ev == MG_EV_HTTP_MSG) {
    struct mg_http_message *hm = (struct mg_http_message *) ev_data;

    // Überprüfen, ob die URI "/test" angefragt wird
    if (mg_match(hm->uri,mg_str("/test"),NULL)) {  // mg_vcmp vergleicht URI
      mg_http_reply(c, 200, "Content-Type: application/json\r\n", s_response);
    } else {
      mg_http_reply(c, 404, "", "404 Not FoundA\n");
      printf("404 Not FoundA\n");
      printf("Angefragte URI: '%.*s'\n", (int)hm->uri.len, hm->uri.buf);
    }
  }
}

int main(void) {
  struct mg_mgr mgr;                       // Event Manager deklarieren
  mg_mgr_init(&mgr);                       // Event Manager initialisieren

  // Starte den HTTP-Server und registriere den Event-Handler
  struct mg_connection *conn = mg_http_listen(&mgr, "http://localhost:8080", handle_request, &mgr);
  if (conn == NULL) {
    printf("Error starting server on port 8080\n");
    return 1;
  }
  printf("Server läuft auf http://localhost:8080/test\n");

  // Endlosschleife für das Event-Handling
  for (;;) {
    mg_mgr_poll(&mgr, 1000);  // Warte auf Ereignisse (1000ms Polling)
  }

  mg_mgr_free(&mgr);  // Speicher freigeben
  return 0;
}