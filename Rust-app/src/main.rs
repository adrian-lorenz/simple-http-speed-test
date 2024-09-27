use axum::{routing::get, Router, Json};
use serde::Serialize;
use std::net::SocketAddr;


#[derive(Serialize)]
struct TestResponse {
    message: &'static str,
}

#[tokio::main]
async fn main() {

    let app = Router::new().route("/test", get(test_handler));
    let addr = SocketAddr::from(([127, 0, 0, 1], 8080));
    println!("Server läuft auf http://{}", addr);
    axum::Server::bind(&addr)
        .serve(app.into_make_service())
        .await
        .unwrap();
}

async fn test_handler() -> Json<TestResponse> {
    Json(TestResponse {
        message: "Hello, this is a test response",
    })
}
