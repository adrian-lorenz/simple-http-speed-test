var builder = WebApplication.CreateBuilder(args);

builder.Services.AddEndpointsApiExplorer();
builder.Services.AddSwaggerGen();

var app = builder.Build();

if (app.Environment.IsDevelopment())
{
    app.UseSwagger();
    app.UseSwaggerUI();
}

app.UseHttpsRedirection();

app.MapGet("/test", () =>
        Results.Json(new { message = "Hello, this is a test response" })  // JSON-Antwort
).WithName("TestEndpoint").WithOpenApi();

app.Run();