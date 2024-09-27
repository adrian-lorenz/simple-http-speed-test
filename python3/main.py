from fastapi import FastAPI
from fastapi.responses import JSONResponse

app = FastAPI()

@app.get("/test")
async def get_test():
    return JSONResponse(content={"message": "Hello, this is a test response"})

if __name__ == "__main__":
    import uvicorn
    uvicorn.run(app, host="0.0.0.0", port=8080)
