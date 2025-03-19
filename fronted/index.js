const express = require("express");
const path = require("path");

const app = express();
const PORT = 4000;

// Servir archivos estáticos del frontend
app.use(express.static(path.join(__dirname, "public")));

app.get("/", (req, res) => {
    res.sendFile(path.join(__dirname, "public", "index.html"));
});

app.listen(PORT, () => {
    console.log(`🌍 Frontend disponible en http://localhost:${PORT}`);
});
