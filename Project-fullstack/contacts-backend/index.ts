import { Hono } from 'hono';
/*import { logger } from 'hono/logger';
import { cors } from 'hono/cors';
import { pool } from './db/index';
import contacts from './routes/contacts';*/

const app = new Hono();

app.get('/', (c) => {
  return c.text('Testingggggg');
});

export default {
  port: 3000,
  fetch: app.fetch,
};