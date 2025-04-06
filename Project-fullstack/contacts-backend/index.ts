import { Hono } from 'hono';
import { logger } from 'hono/logger';
import { cors } from 'hono/cors';
import { pool } from './db/index';
import contacts from './routes/contacts';

const app = new Hono();

app.use('*', logger());
app.use('*', cors());

app.get('/test-db', async (c) => {
  const result = await pool.query('SELECT NOW()');
  return c.json({ time: result.rows[0] });
});

app.route('contacts', contacts);

export default {
    port: 3000,
    fetch: app.fetch,
};